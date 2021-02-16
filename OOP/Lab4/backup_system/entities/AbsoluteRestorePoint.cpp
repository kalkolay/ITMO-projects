#include "AbsoluteRestorePoint.h"

#include <numeric>

namespace backup::entities
{
    AbsoluteRestorePoint::AbsoluteRestorePoint()
        : m_size( 0 )
    {
        auto now       = std::chrono::system_clock::now();
        m_creationTime = utils::time_to_string(now);
    }

    AbsoluteRestorePoint::AbsoluteRestorePoint(const Files& files)
        : m_files( files )
    {
        auto now       = std::chrono::system_clock::now();
        m_creationTime = utils::time_to_string(now);
        std::uintmax_t totalSize = 0;
        for (const auto& file : files)
            totalSize += file.GetSize();
        m_size = totalSize;
    }

    std::string AbsoluteRestorePoint::GetCreationTime() const
    {
        return m_creationTime;
    }

    Files AbsoluteRestorePoint::GetBackupFiles() const
    {
        return m_files;
    }

    std::uintmax_t AbsoluteRestorePoint::GetSize() const
    {
        return m_size;
    }

    bool AbsoluteRestorePoint::operator ==(const AbsoluteRestorePoint& other) const
    {
        return m_files == other.m_files;
    }
}