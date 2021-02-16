#pragma once

#include "FileInfo.h"

namespace backup::entities
{
    class IncrementalRestorePoint
    {
    public:
        IncrementalRestorePoint();
        explicit IncrementalRestorePoint(const Files& newFiles);
        explicit IncrementalRestorePoint(IncrementalRestorePoint* prevPoint,
                                         const Files&             newFiles);

        [[nodiscard]] std::string    GetCreationTime   () const;
        [[nodiscard]] Files          GetBackupFilesDiff() const;
        [[nodiscard]] std::uintmax_t GetSize           () const;

        // TODO: Restore diff files by parsing

    private:
        std::string    m_creationTime;
        Files          m_filesDiff;
        std::uintmax_t m_size;
    };
}