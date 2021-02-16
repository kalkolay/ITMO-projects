#pragma once

#include "FileInfo.h"

namespace backup::entities
{
    class AbsoluteRestorePoint
    {
    public:
        AbsoluteRestorePoint();
        explicit AbsoluteRestorePoint(const Files& files);

        [[nodiscard]] std::string    GetCreationTime() const;
        [[nodiscard]] Files          GetBackupFiles () const;
        [[nodiscard]] std::uintmax_t GetSize        () const;

        bool operator ==(const AbsoluteRestorePoint& other) const;

    private:
        std::string    m_creationTime;
        Files          m_files;
        std::uintmax_t m_size;
    };
}