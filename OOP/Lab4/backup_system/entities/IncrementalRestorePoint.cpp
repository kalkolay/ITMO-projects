#include "IncrementalRestorePoint.h"

#include <numeric>

namespace backup::entities
{
    IncrementalRestorePoint::IncrementalRestorePoint()
        : m_size( 0 )
    {
        auto now       = std::chrono::system_clock::now();
        m_creationTime = utils::time_to_string(now);
    }

    IncrementalRestorePoint::IncrementalRestorePoint(const Files& newFiles)
        : m_filesDiff(newFiles)
    {
        auto now       = std::chrono::system_clock::now();
        m_creationTime = utils::time_to_string(now);
        std::uintmax_t totalSize = 0;
        for (const auto& file : newFiles)
            totalSize += file.GetSize();
        m_size = totalSize;
    }

    IncrementalRestorePoint::IncrementalRestorePoint(IncrementalRestorePoint* prevPoint,
                                                     const Files&             newFiles)
    {
        auto now       = std::chrono::system_clock::now();
        m_creationTime = utils::time_to_string(now);
        /// Create files diff
        Files oldFiles = prevPoint->GetBackupFilesDiff();
        std::vector<std::string> oldFilesNames;
        for ( const auto& file : oldFiles )
            oldFilesNames.push_back( file.GetName() );
        std::vector<std::string> newFilesNames;
        for (const auto& file : newFiles)
            newFilesNames.push_back( file.GetName() );
        std::vector<std::string> modifiedFilesNames = utils::find_intersection( oldFilesNames, newFilesNames );
        Files filesDiff;
        for (const auto& fileName : modifiedFilesNames)
        {
            auto oldFileIt = std::find( oldFiles.begin(), oldFiles.end(), FileInfo(fileName) );
            auto newFileIt = std::find( newFiles.begin(), newFiles.end(), FileInfo(fileName) );
            if ( oldFileIt != oldFiles.end() && newFileIt != newFiles.end() )
            {
                std::string command = "diff "
                                    + oldFileIt->GetFile().string()
                                    + " "
                                    + newFileIt->GetFile().string()
                                    + " > temp";
                system( command.c_str() );
                FileInfo temp("temp");
                filesDiff.push_back(temp);
                //fs::remove( temp.GetFile() );
            }
        }
        m_filesDiff = filesDiff;
        std::uintmax_t totalSize = 0;
        for (const auto& file : filesDiff)
            totalSize += file.GetSize();
        m_size = totalSize;
    }

    std::string IncrementalRestorePoint::GetCreationTime() const
    {
        return m_creationTime;
    }

    Files IncrementalRestorePoint::GetBackupFilesDiff() const
    {
        return m_filesDiff;
    }

    std::uintmax_t IncrementalRestorePoint::GetSize() const
    {
        return m_size;
    }
}