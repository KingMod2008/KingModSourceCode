#include "SimpleImGuiFileBrowser.hpp"
#include <windows.h>
#include <shlobj.h>
#include <algorithm>
#include <ctype.h>

namespace
{
    std::string NormalizeExtension(std::string extension)
    {
        std::transform(extension.begin(), extension.end(), extension.begin(), ::tolower);
        return extension;
    }
}

SimpleImGuiFileBrowser::SimpleImGuiFileBrowser()
    : m_isOpen(false), m_hasSelected(false), m_title("Select File")
{
    memset(m_searchBuffer, 0, sizeof(m_searchBuffer));
    m_currentDir = fs::current_path();
}

void SimpleImGuiFileBrowser::SetTitle(const std::string& title)
{
    m_title = title;
}

void SimpleImGuiFileBrowser::SetAllowedExtensions(const std::vector<std::string>& extensions)
{
    m_allowedExtensions.clear();
    m_allowedExtensions.reserve(extensions.size());

    for (const std::string& extension : extensions)
    {
        if (!extension.empty())
            m_allowedExtensions.push_back(NormalizeExtension(extension));
    }
}

void SimpleImGuiFileBrowser::ClearAllowedExtensions()
{
    m_allowedExtensions.clear();
}

void SimpleImGuiFileBrowser::Open()
{
    m_isOpen = true;
    m_hasSelected = false;
    m_selectedFile.clear();
    memset(m_searchBuffer, 0, sizeof(m_searchBuffer));
    Refresh();
}

void SimpleImGuiFileBrowser::Close()
{
    m_isOpen = false;
}

bool SimpleImGuiFileBrowser::IsOpened() const
{
    return m_isOpen;
}

bool SimpleImGuiFileBrowser::HasSelected() const
{
    return m_hasSelected;
}

fs::path SimpleImGuiFileBrowser::GetSelected() const
{
    return m_selectedFile;
}

void SimpleImGuiFileBrowser::ClearSelected()
{
    m_hasSelected = false;
    m_selectedFile.clear();
}

std::string SimpleImGuiFileBrowser::GetWindowsSpecialFolder(int csidl)
{
    char path[MAX_PATH];
    if (SUCCEEDED(SHGetFolderPathA(NULL, csidl, NULL, 0, path))) {
        return std::string(path);
    }
    return "";
}

void SimpleImGuiFileBrowser::Refresh()
{
    m_files.clear();
    try {
        if (m_currentDir.has_parent_path() && m_currentDir != m_currentDir.parent_path()) {
            m_files.push_back({ m_currentDir.parent_path(), true, ".." });
        }
        for (const auto& entry : fs::directory_iterator(m_currentDir)) {
            bool isDir = entry.is_directory();
            std::string name = entry.path().filename().string();
            if (!isDir) {
                const std::string ext = NormalizeExtension(entry.path().extension().string());
                if (!m_allowedExtensions.empty()) {
                    if (std::find(m_allowedExtensions.begin(), m_allowedExtensions.end(), ext) == m_allowedExtensions.end())
                        continue;
                } else if (ext != ".png" && ext != ".jpg" && ext != ".jpeg" && ext != ".bmp" && ext != ".tga") {
                    continue;
                }
            }
            m_files.push_back({ entry.path(), isDir, name });
        }
        std::sort(m_files.begin(), m_files.end(), [](const FileInfo& a, const FileInfo& b) {
            if (a.isDir != b.isDir) return a.isDir > b.isDir;
            return a.name < b.name;
        });
    } catch (...) {}
}

void SimpleImGuiFileBrowser::Display()
{
    if (!m_isOpen) return;

    ImGui::SetNextWindowSize(ImVec2(700, 450), ImGuiCond_FirstUseEver);
    if (ImGui::Begin(m_title.c_str(), &m_isOpen, ImGuiWindowFlags_NoCollapse)) {
        
        ImGui::BeginChild("ShortcutsPane", ImVec2(150, 0), true);
        ImGui::TextColored(ImVec4(1.0f, 0.5f, 0.5f, 1.0f), "Shortcuts");
        ImGui::Separator();
        
        if (ImGui::Selectable("Desktop")) {
            m_currentDir = GetWindowsSpecialFolder(CSIDL_DESKTOP);
            Refresh();
        }
        if (ImGui::Selectable("Downloads")) {
                                        
            std::string profile = GetWindowsSpecialFolder(CSIDL_PROFILE);
            if (!profile.empty()) {
                m_currentDir = fs::path(profile) / "Downloads";
                Refresh();
            }
        }
        if (ImGui::Selectable("Documents")) {
            m_currentDir = GetWindowsSpecialFolder(CSIDL_MYDOCUMENTS);
            Refresh();
        }
        if (ImGui::Selectable("Pictures")) {
            m_currentDir = GetWindowsSpecialFolder(CSIDL_MYPICTURES);
            Refresh();
        }
        ImGui::Separator();
                 
        DWORD drives = GetLogicalDrives();
        for (int i = 0; i < 26; ++i) {
            if (drives & (1 << i)) {
                char driveStr[4] = { (char)('A' + i), ':', '\\', '\0' };
                if (ImGui::Selectable(driveStr)) {
                    m_currentDir = fs::path(driveStr);
                    Refresh();
                }
            }
        }
        ImGui::EndChild();

        ImGui::SameLine();

        ImGui::BeginGroup();
                   
        ImGui::Text("Path:");
        ImGui::SameLine();
        std::string currentPathStr = m_currentDir.string();
        char pathBuf[512];
        strncpy_s(pathBuf, currentPathStr.c_str(), sizeof(pathBuf));
        if (ImGui::InputText("##path", pathBuf, sizeof(pathBuf), ImGuiInputTextFlags_EnterReturnsTrue)) {
            fs::path p(pathBuf);
            if (fs::exists(p) && fs::is_directory(p)) {
                m_currentDir = p;
                Refresh();
            }
        }
        ImGui::SameLine();
        if (ImGui::Button("Refresh")) {
            Refresh();
        }

        ImGui::InputText("Search", m_searchBuffer, sizeof(m_searchBuffer));

                    
        ImGui::BeginChild("FilePane", ImVec2(0, -ImGui::GetFrameHeightWithSpacing()), true);
        
        std::string searchLower = m_searchBuffer;
        std::transform(searchLower.begin(), searchLower.end(), searchLower.begin(), ::tolower);

        for (const auto& f : m_files) {
            if (!searchLower.empty()) {
                std::string nameLower = f.name;
                std::transform(nameLower.begin(), nameLower.end(), nameLower.begin(), ::tolower);
                if (nameLower.find(searchLower) == std::string::npos) continue;
            }

            std::string icon = "[Img] ";
            if (f.isDir)
                icon = "[Dir] ";
            else if (!m_allowedExtensions.empty())
                icon = "[File] ";
            std::string label = icon + f.name;
            
            bool isSelected = (m_selectedFile == f.path && !f.isDir);
            
            if (ImGui::Selectable(label.c_str(), isSelected, ImGuiSelectableFlags_AllowDoubleClick)) {
                if (f.isDir) {
                    if (ImGui::IsMouseDoubleClicked(0)) {
                        m_currentDir = f.path;
                        Refresh();
                    }
                } else {
                    m_selectedFile = f.path;
                    if (ImGui::IsMouseDoubleClicked(0)) {
                        m_hasSelected = true;
                        m_isOpen = false;
                    }
                }
            }
        }
        ImGui::EndChild();

                                      
        ImGui::Text("Selected:");
        ImGui::SameLine();
        std::string selStr = m_selectedFile.filename().string();
        ImGui::TextColored(ImVec4(0.2f, 1.0f, 0.2f, 1.0f), "%s", selStr.c_str());
        
        ImGui::SameLine(ImGui::GetWindowWidth() - 120);
        if (ImGui::Button("Cancel", ImVec2(50, 0))) {
            m_isOpen = false;
        }
        ImGui::SameLine();
        if (ImGui::Button("Open", ImVec2(50, 0)) && !m_selectedFile.empty() && !fs::is_directory(m_selectedFile)) {
            m_hasSelected = true;
            m_isOpen = false;
        }

        ImGui::EndGroup();
    }
    ImGui::End();
}
