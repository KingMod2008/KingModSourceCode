import contextlib
import io
import os
from pathlib import Path
import tempfile
import unittest
from unittest.mock import patch

import publish


class PublishTests(unittest.TestCase):
    def test_local_remote_upload_and_update(self):
        with tempfile.TemporaryDirectory(prefix="kingmod-upload-test-") as temporary:
            base = Path(temporary)
            root, remote = base / "source", base / "remote.git"
            root.mkdir()
            remote.mkdir()
            publish.git(remote, "init", "--bare", "-b", "main")
            (root / ".gitignore").write_text("ignored.txt\n")
            (root / "README.md").write_text("First publication")
            (root / "ignored.txt").write_text("Must stay local")
            for relative in ["RocketSim/build/Release/RocketSim.lib", "x64/Release/KingMod.dll", ".vs/cache", "config.env", "private.key"]:
                path = root / relative
                path.parent.mkdir(parents=True, exist_ok=True)
                path.write_text("Excluded")
            dependency = root / "ImGui/freetype/freetype.lib"
            dependency.parent.mkdir(parents=True)
            dependency.write_bytes(b"Test fixture")
            environment = {"GIT_AUTHOR_NAME": "Upload Test", "GIT_AUTHOR_EMAIL": "test@example.invalid", "GIT_COMMITTER_NAME": "Upload Test", "GIT_COMMITTER_EMAIL": "test@example.invalid", "GIT_CONFIG_COUNT": "2", "GIT_CONFIG_KEY_0": "user.name", "GIT_CONFIG_VALUE_0": "Upload Test", "GIT_CONFIG_KEY_1": "user.email", "GIT_CONFIG_VALUE_1": "test@example.invalid"}
            with patch.dict(os.environ, environment), contextlib.redirect_stdout(io.StringIO()):
                publish.publish(root, str(remote), "main", "First", False)
                files = publish.git(remote, "ls-tree", "-r", "--name-only", "main").decode().splitlines()
                self.assertEqual(set(files), {".gitignore", "README.md", "ImGui/freetype/freetype.lib"})
                (root / "README.md").write_text("Updated publication")
                dependency.unlink()
                publish.publish(root, str(remote), "main", "Update", False)
                self.assertEqual(publish.git(remote, "show", "main:README.md"), b"Updated publication")
                self.assertEqual(publish.git(remote, "show", "main:ImGui/freetype/freetype.lib"), b"Test fixture")
                self.assertEqual(publish.git(remote, "rev-list", "--count", "main").strip(), b"2")
                self.assertFalse((root / ".git").exists())

    def test_secret_and_unexpected_binary_are_rejected(self):
        with tempfile.TemporaryDirectory() as temporary:
            root = Path(temporary)
            (root / "settings.json").write_text('{"key":"ghp_' + 'a' * 36 + '"}')
            with self.assertRaisesRegex(RuntimeError, "Possible credential"):
                publish.validate(root, ["settings.json"])
            (root / "payload.dll").write_bytes(b"Test fixture")
            with self.assertRaisesRegex(RuntimeError, "Excluded file"):
                publish.validate(root, ["payload.dll"])

    def test_preview_is_offline(self):
        with tempfile.TemporaryDirectory() as temporary:
            root = Path(temporary)
            (root / ".gitignore").write_text("")
            (root / "README.md").write_text("Preview only")
            with contextlib.redirect_stdout(io.StringIO()):
                publish.publish(root, "https://invalid.example/not-contacted.git", "main", "Preview", True)
            self.assertFalse((root / ".git").exists())


if __name__ == "__main__":
    unittest.main()
