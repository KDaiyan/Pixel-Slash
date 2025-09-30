#pragma once

#include <filesystem>

class FilePath {
public:
    explicit FilePath(const std::string& directory) : FilePath(std::filesystem::path(directory)) {}
    explicit FilePath(const char* directory) : FilePath(std::filesystem::path(directory)) {}
    FilePath() = delete;

    [[nodiscard]] const std::filesystem::path& get() const { return m_path; }

private:
    explicit FilePath(const std::filesystem::path& directory) {
        if (directory.is_absolute()) {
            m_path = directory;
        } else {
            m_path = std::filesystem::path(ROOT_DIR) / directory;
        }
    }

    std::filesystem::path m_path;
};
