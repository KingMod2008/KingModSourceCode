#pragma once
#include <string>
#include <vector>
#include <filesystem>
#include "imgui.h"

namespace fs = std::filesystem;

class SimpleImGuiFileBrowser {
public:
    SimpleImGuiFileBrowser();
    void Open();
    void Close();
    bool IsOpened() const;
    void Display();
    bool HasSelected() const;
    fs::path GetSelected() const;
    void ClearSelected();
    void SetTitle(const std::string& title);
    void SetAllowedExtensions(const std::vector<std::string>& extensions);
    void ClearAllowedExtensions();

private:
    void Refresh();
    std::string GetWindowsSpecialFolder(int csidl);

    bool m_isOpen;
    bool m_hasSelected;
    fs::path m_selectedFile;
    fs::path m_currentDir;
    std::string m_title;
    char m_searchBuffer[256];

    struct FileInfo {
        fs::path path;
        bool isDir;
        std::string name;
    };
    std::vector<FileInfo> m_files;
    std::vector<std::string> m_allowedExtensions;
};
