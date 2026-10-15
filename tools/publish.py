import argparse
import os
from pathlib import Path
import re
import shutil
import subprocess
import sys
import tempfile

DEFAULT_REPOSITORY = "https://github.com/KingMod2008/KingModSourceCode.git"
ROOT = Path(__file__).resolve().parents[1]
BLOCKED_DIRS = {".git", ".vs", ".dbg", "build", "build-injector", "out", "x64", "x86", "debug", "release", "__pycache__", "node_modules"}
BLOCKED_SUFFIXES = {".exe", ".sys", ".obj", ".pdb", ".ilk", ".iobj", ".ipdb", ".exp", ".tlog", ".log", ".user", ".suo", ".rar", ".zip", ".7z", ".pem", ".key", ".pfx", ".p12", ".dmp", ".pyc", ".env"}
BUNDLED_BINARIES = {
    "imgui/freetype/freetype.lib",
    "rlsdk/rpc_discord/win32-dynamic/bin/discord-rpc.dll",
    "rlsdk/rpc_discord/win64-dynamic/bin/discord-rpc.dll",
    "rlsdk/rpc_discord/win32-dynamic/lib/discord-rpc.lib",
    "rlsdk/rpc_discord/win64-dynamic/lib/discord-rpc.lib",
}
SECRET_PATTERNS = [
    re.compile(rb"-----BEGIN (?:RSA |EC |OPENSSH )?PRIVATE KEY-----"),
    re.compile(rb"\bgh[pousr]_[A-Za-z0-9]{30,}\b"),
    re.compile(rb"\bAKIA[0-9A-Z]{16}\b"),
    re.compile(rb"https://(?:discord(?:app)?\.com)/api/webhooks/\d+/[A-Za-z0-9_-]+"),
]


def git(directory, *args, input_data=None, allowed=(0,)):
    result = subprocess.run(["git", "-C", str(directory), *args], input=input_data, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    if result.returncode not in allowed:
        raise RuntimeError(result.stderr.decode(errors="replace").strip() or "Git command failed")
    return result.stdout


def blocked(relative):
    path = Path(relative)
    parts = [part.lower() for part in path.parts]
    return (
        any(part in BLOCKED_DIRS or part.startswith("cmake-build-") for part in parts[:-1])
        or parts[0] == "kingmod"
        or path.suffix.lower() in BLOCKED_SUFFIXES
        or path.name.lower().startswith(".env")
        or path.name.lower() in {"thumbs.db", "desktop.ini", "credentials.json", "secrets.json"}
        or ".bak" in path.name.lower()
        or (path.suffix.lower() in {".dll", ".lib"} and path.as_posix().lower() not in BUNDLED_BINARIES)
    )


def candidates(root):
    output = []
    for directory, dirs, files in os.walk(root, followlinks=False):
        dirs[:] = [name for name in dirs if not (Path(directory) / name).is_symlink() and not getattr(Path(directory) / name, "is_junction", lambda: False)() and not blocked((Path(directory) / name / "placeholder").relative_to(root))]
        for name in files:
            path = Path(directory) / name
            relative = path.relative_to(root).as_posix()
            if not path.is_symlink() and not blocked(relative):
                if hasattr(path, "is_junction") and path.is_junction():
                    continue
                output.append(relative)
    return sorted(output)


def validate(root, paths):
    total = 0
    for relative in paths:
        if blocked(relative):
            raise RuntimeError("Excluded file is tracked by the remote repository: " + relative)
        path = root / relative
        if path.is_symlink() or not path.resolve().is_relative_to(root.resolve()):
            raise RuntimeError("Symlink or outside-workspace file: " + relative)
        size = path.stat().st_size
        total += size
        if size >= 100 * 1024 * 1024:
            raise RuntimeError("File exceeds upload size limit: " + relative)
        if path.suffix.lower() not in {".png", ".jpg", ".jpeg", ".ttf", ".cmf", ".dll", ".lib"}:
            data = path.read_bytes()
            if any(pattern.search(data) for pattern in SECRET_PATTERNS):
                raise RuntimeError("Possible credential found; inspect this file: " + relative)
    return total


def publish(root, repository, branch, message, dry_run):
    if not shutil.which("git"):
        raise RuntimeError("Install Git for Windows first.")
    if not re.fullmatch(r"[A-Za-z0-9][A-Za-z0-9._/-]*", branch) or ".." in branch:
        raise RuntimeError("Invalid branch name")
    with tempfile.TemporaryDirectory(prefix="kingmod-publish-") as temporary:
        checkout = Path(temporary) / "repository"
        if dry_run:
            checkout.mkdir()
            git(checkout, "init", "-b", branch)
        else:
            result = subprocess.run(["git", "clone", "--", repository, str(checkout)], capture_output=True)
            if result.returncode:
                raise RuntimeError("Clone failed. Check repository access and Git credentials.\n" + result.stderr.decode(errors="replace"))
            refs = git(checkout, "for-each-ref", "--format=%(refname)", "refs/remotes/origin/").decode()
            if refs.strip():
                if "refs/remotes/origin/" + branch not in refs.splitlines():
                    raise RuntimeError("Requested branch is absent from the nonempty remote repository.")
                git(checkout, "checkout", "-B", branch, "origin/" + branch)
            else:
                git(checkout, "checkout", "-B", branch)
        shutil.copyfile(root / ".gitignore", checkout / ".gitignore")
        paths = candidates(root)
        ignored = git(checkout, "check-ignore", "--no-index", "-z", "--stdin", input_data="\0".join(paths).encode() + b"\0", allowed=(0, 1))
        ignored = set(ignored.decode().strip("\0").split("\0"))
        paths = [path for path in paths if path not in ignored]
        total = validate(root, paths)
        print(f"{len(paths)} files, {total / 1024 / 1024:.1f} MiB -> {repository} [{branch}]")
        for relative in paths:
            destination = checkout / relative
            if destination.is_symlink() or not destination.resolve().is_relative_to(checkout.resolve()):
                raise RuntimeError("Remote path is a symlink or escapes the checkout: " + relative)
            destination.parent.mkdir(parents=True, exist_ok=True)
            shutil.copyfile(root / relative, destination)
        git(checkout, "add", "--all")
        tracked = git(checkout, "ls-files", "-z").decode().strip("\0").split("\0")
        validate(checkout, [path for path in tracked if path])
        print(git(checkout, "diff", "--cached", "--stat").decode(errors="replace"))
        if dry_run:
            print("Preview passed. No commit, upload, or workspace Git changes were made.")
            return
        if not git(checkout, "diff", "--cached", "--name-only").strip():
            print("Already up to date.")
            return
        for setting in ["user.name", "user.email"]:
            if not git(checkout, "config", "--get", setting, allowed=(0, 1)).strip():
                raise RuntimeError("Set your Git " + setting + " before publishing.")
        git(checkout, "commit", "-m", message)
        git(checkout, "push", "origin", "HEAD:refs/heads/" + branch)
        print("Published successfully. Existing remote-only files were preserved; no force push was used.")


def main():
    parser = argparse.ArgumentParser(description="Publish KingMod source and showcase; exclude builds and private files.")
    parser.add_argument("--dry-run", action="store_true", help="Offline preview without committing or uploading")
    parser.add_argument("--repository", default=DEFAULT_REPOSITORY)
    parser.add_argument("--branch", default="main")
    parser.add_argument("--message", default="Publish KingMod source and showcase")
    args = parser.parse_args()
    try:
        publish(ROOT, args.repository, args.branch, args.message, args.dry_run)
    except (OSError, RuntimeError) as error:
        print("Publish stopped: " + str(error), file=sys.stderr)
        return 1
    return 0


if __name__ == "__main__":
    sys.exit(main())
