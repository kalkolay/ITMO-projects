#include "FileInfo.h"

namespace backup::entities
{
    FileInfo::FileInfo(const std::string& filename)
        : m_name         ( filename )
        , m_extension    ( m_name.extension() )
        , m_parentDir    ( m_name.parent_path() )
        , m_size         ( fs::file_size(m_name) )
    {
        auto fileTime   = fs::last_write_time(m_name);
        m_lastWriteTime = utils::time_to_string(fileTime);
    }

    fs::path FileInfo::GetFile() const
    {
        return m_name;
    }

    std::string FileInfo::GetName() const
    {
        return GetFile().filename();
    }

    std::string FileInfo::GetExtension() const
    {
        return m_extension.string();
    }

    std::string FileInfo::GetParentPath() const
    {
        return m_parentDir.string();
    }

    std::uintmax_t FileInfo::GetSize() const
    {
        return m_size;
    }

    std::string FileInfo::GetLastWriteTime() const
    {
        return m_lastWriteTime;
    }

    bool FileInfo::operator ==(const FileInfo& other) const
    {
        return GetFile() == other.GetFile();
    }
}
