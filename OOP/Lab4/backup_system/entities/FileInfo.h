#pragma once

#include "../utilities/Utilities.h"

#include <filesystem>
#include <vector>

namespace fs = std::filesystem;

namespace backup::entities
{
    class FileInfo
    {
    public:
        explicit FileInfo(const std::string& filename);

        [[nodiscard]] fs::path       GetFile         () const;
        [[nodiscard]] std::string    GetName         () const;
        [[nodiscard]] std::string    GetExtension    () const;
        [[nodiscard]] std::string    GetParentPath   () const;
        [[nodiscard]] std::uintmax_t GetSize         () const;
        [[nodiscard]] std::string    GetLastWriteTime() const;

        bool operator ==(const FileInfo& other) const;

        //TODO: Add filesystem status?

    private:
        fs::path           m_name;
        fs::path           m_extension;
        fs::path           m_parentDir;
        std::uintmax_t     m_size;
        std::string        m_lastWriteTime;
    };

    using Files = std::vector<FileInfo>;
}