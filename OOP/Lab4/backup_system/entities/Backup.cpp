#include "Backup.h"

#include <utility>

namespace backup::entities
{
    std::time_t string_to_time(const std::string& tp)
    {
        struct std::tm tm{};
        std::istringstream ss(tp);
        ss >> std::get_time(&tm, "%A, %d %B %Y %H:%M");
        return mktime(&tm);
    }

    double time_diff(const std::string& end, const std::string& begin)
    {
        std::time_t endTime = string_to_time(end), beginTime = string_to_time(begin);
        return difftime(endTime, beginTime);
    }

    Backup::Backup()
    {
        boost::uuids::random_generator uuid_gen;
        m_id = uuid_gen();
        auto now       = std::chrono::system_clock::now();
        m_creationTime = utils::time_to_string(now);
        m_size = 0;
    }

    Backup::Backup(const Files& files)
        : m_files(files)
    {
        boost::uuids::random_generator uuid_gen;
        m_id = uuid_gen();
        auto now       = std::chrono::system_clock::now();
        m_creationTime = utils::time_to_string(now);
        std::uintmax_t totalSize = 0;
        for (const auto& file : files)
            totalSize += file.GetSize();
        m_size = totalSize;
    }

    uuid_t Backup::GetId() const
    {
        return m_id;
    }

    std::string Backup::GetCreationTime() const
    {
        return m_creationTime;
    }

    std::uintmax_t Backup::GetSize() const
    {
        return m_size;
    }

    RestorePoints Backup::GetRestorePoints() const
    {
        return m_restorePoints;
    }

    Files Backup::GetFiles() const
    {
        return m_files;
    }

    void Backup::AddFile(const FileInfo& file)
    {
        m_files.push_back(file);
        m_size += file.GetSize();
    }

    void Backup::RemoveFile(const FileInfo& file)
    {
        m_files.erase( std::remove(m_files.begin(), m_files.end(), file), m_files.end() );
        m_size -= file.GetSize();
    }

    void Backup::PerformStorageAlgorithm(ETypeStorage algorithm)
    {
        switch (algorithm)
        {
            case Separate:
                if ( !fs::exists("backup_separate") )
                    fs::create_directory("backup_separate");
                for (const auto& file : m_files)
                {
                    fs::path copiedFile = fs::path("backup_separate") / file.GetFile();
                    if ( !fs::exists(copiedFile) )
                        fs::copy_file( file.GetFile(), copiedFile );
                }
                break;
            case Common:
                if ( !fs::exists("backup_common") )
                    fs::create_directory("backup_common");
                for (const auto& file : m_files)
                {
                    fs::path copiedFile = fs::path("backup_common") / file.GetFile();
                    if ( !fs::exists(copiedFile) )
                        fs::copy_file( file.GetFile(), copiedFile );
                }
                system("zip -r backup_common.zip backup_common");
                fs::remove_all("backup_common");
                break;
            default:
                break;
        }
    }

    void Backup::CreateAbsoluteRestorePoint(ETypeStorage algorithm)
    {
        m_restorePoints.push_back( AbsoluteRestorePoint(m_files) );
        PerformStorageAlgorithm(algorithm);
    }

    void Backup::DeleteAbsoluteRestorePoint(const AbsoluteRestorePoint& restorePoint)
    {
        m_restorePoints.erase(
                std::remove_if(
                        m_restorePoints.begin(),
                        m_restorePoints.end(),
                        [&restorePoint](const auto& v) {
                            return std::visit(
                                    [&](const auto& obj) {
                                            return obj.GetCreationTime() == restorePoint.GetCreationTime();
                                        },
                                    v);
                        }),
                        m_restorePoints.end());
    }

    void Backup::CreateIncrementalRestorePoint(IncrementalRestorePoint* prevPoint, ETypeStorage algorithm)
    {
        if (prevPoint != nullptr)
            m_restorePoints.push_back( IncrementalRestorePoint(prevPoint, m_files) );
        else
            m_restorePoints.push_back( IncrementalRestorePoint(m_files) );
        PerformStorageAlgorithm(algorithm);
    }

    void Backup::DeleteIncrementalRestorePoint(const IncrementalRestorePoint& restorePoint)
    {
        m_restorePoints.erase(
                std::remove_if(
                        m_restorePoints.begin(),
                        m_restorePoints.end(),
                        [&restorePoint](const auto& v) {
                            return std::visit(
                                    [&](const auto& obj) {
                                        return obj.GetCreationTime() == restorePoint.GetCreationTime();
                                    },
                                    v);
                        }),
                m_restorePoints.end());
    }

    void Backup::CleanRestorePointsByNumber(unsigned number)
    {
        m_restorePoints.resize(m_restorePoints.size() - number);
    }

    unsigned Backup::CleanRestorePointsByNumberCount(unsigned number)
    {
        return m_restorePoints.size() - number;
    }

    void Backup::CleanRestorePointsByDate(const std::string& date)
    {
        m_restorePoints.erase(
                std::remove_if(
                        m_restorePoints.begin(),
                        m_restorePoints.end(),
                        [&date](const auto& v) {
                            return std::visit(
                                    [&](const auto& point) {
                                        return time_diff( date, point.GetCreationTime() ) > 0;
                                    },
                                    v);
                        }),
                m_restorePoints.end());
    }

    unsigned Backup::CleanRestorePointsByDateCount(const std::string& date)
    {
        RestorePoints tempRestorePoints = m_restorePoints;
        std::size_t prevSize = tempRestorePoints.size();
        tempRestorePoints.erase(
                std::remove_if(
                        tempRestorePoints.begin(),
                        tempRestorePoints.end(),
                        [&date](const auto& v) {
                            return std::visit(
                                    [&](const auto& point) {
                                        return time_diff( date, point.GetCreationTime() ) > 0;
                                    },
                                    v);
                        }),
                tempRestorePoints.end());
        return prevSize - tempRestorePoints.size();
    }

    void Backup::CleanRestorePointsBySize(std::uintmax_t size)
    {
        m_restorePoints.erase(
                std::remove_if(
                        m_restorePoints.begin(),
                        m_restorePoints.end(),
                        [&size](const auto& v) {
                            return std::visit(
                                    [&](const auto& point) {
                                        return point.GetSize() > size;
                                    },
                                    v);
                        }),
                m_restorePoints.end());
    }

    unsigned Backup::CleanRestorePointsBySizeCount(std::uintmax_t size)
    {
        RestorePoints tempRestorePoints = m_restorePoints;
        std::size_t prevSize = tempRestorePoints.size();
        tempRestorePoints.erase(
                std::remove_if(
                        tempRestorePoints.begin(),
                        tempRestorePoints.end(),
                        [&size](const auto& v) {
                            return std::visit(
                                    [&](const auto& point) {
                                        return point.GetSize() > size;
                                    },
                                    v);
                        }),
                tempRestorePoints.end());
        return prevSize - tempRestorePoints.size();
    }

    unsigned Backup::CleanRestorePointsCount(ETypeCleaning   algorithm,
                                             const std::any& parameter)
    {
        unsigned result = 0;
        switch (algorithm)
        {
            case Number:
                result = CleanRestorePointsByNumberCount( (unsigned)std::any_cast<int>(parameter) );
                break;
            case Date:
                if ( auto* temp = const_cast<std::string *>(std::any_cast<std::string>(&parameter)) )
                    result = CleanRestorePointsByDateCount( *temp );
                break;
            case Size:
                result = CleanRestorePointsBySizeCount( (std::uintmax_t)std::any_cast<int>(parameter) );
                break;
            default:
                break;
        }
        return result;
    }

    void Backup::PerformCleanRestorePointsByType(ETypeCleaning   algorithm,
                                                 const std::any& parameter)
    {
        switch (algorithm)
        {
            case Number:
                CleanRestorePointsByNumber( (unsigned)std::any_cast<int>(parameter) );
                break;
            case Date:
                if ( auto* temp = const_cast<std::string *>(std::any_cast<std::string>(&parameter)) )
                    CleanRestorePointsByDate( *temp );
                break;
            case Size:
                CleanRestorePointsBySize( (std::uintmax_t)std::any_cast<int>(parameter) );
            default:
                break;
        }
    }

    void Backup::CleanRestorePointsHybrid(bool            cleanIfAllFail,
                                          ETypeCleaning   firstAlgorithm,
                                          const std::any& firstParameter,
                                          ETypeCleaning   secondAlgorithm,
                                          const std::any& secondParameter,
                                          ETypeCleaning   thirdAlgorithm,
                                          const std::any& thirdParameter)
    {
        bool hasTwoParameters = false;
        unsigned firstSize = CleanRestorePointsCount(firstAlgorithm, firstParameter);
        unsigned secondSize = CleanRestorePointsCount(secondAlgorithm, secondParameter);
        unsigned thirdSize;
        if (thirdAlgorithm != None && std::any_cast<int>(thirdParameter) != -1)
            thirdSize = CleanRestorePointsCount(firstAlgorithm, firstParameter);
        else
            hasTwoParameters = true;
        if (hasTwoParameters)
        {
            if (cleanIfAllFail)
            {
                firstSize < secondSize && firstSize > 0
                    ? PerformCleanRestorePointsByType(firstAlgorithm, firstParameter)
                    : PerformCleanRestorePointsByType(secondAlgorithm, secondParameter);
            }
            else
            {
                firstSize >= secondSize || !secondSize
                    ? PerformCleanRestorePointsByType(secondAlgorithm, secondParameter)
                    : PerformCleanRestorePointsByType(firstAlgorithm, firstParameter);
            }
        }
        else
        {
            if (cleanIfAllFail)
            {
                unsigned minSize = std::min( firstSize, std::min(secondSize, thirdSize) );
                if (!minSize)
                    return;
                else
                {
                    std::vector<unsigned> temp = { firstSize, secondSize, thirdSize };
                    auto result = (ETypeCleaning)std::distance(temp.begin(),
                                                               std::find(temp.begin(), temp.end(), minSize) );
                    switch (result)
                    {
                        case Number:
                            PerformCleanRestorePointsByType(result, firstParameter);
                            break;
                        case Date:
                            PerformCleanRestorePointsByType(result, secondParameter);
                            break;
                        default:
                            PerformCleanRestorePointsByType(result, thirdParameter);
                            break;
                    }
                }
            }
            else
            {
                unsigned maxSize = std::max( firstSize, std::max(secondSize, thirdSize) );
                if (!maxSize)
                    return;
                else
                {
                    std::vector<unsigned> temp = { firstSize, secondSize, thirdSize };
                    auto result = (ETypeCleaning)std::distance(temp.begin(),
                                                               std::find(temp.begin(), temp.end(), maxSize) );
                    switch (result)
                    {
                        case Number:
                            PerformCleanRestorePointsByType(result, firstParameter);
                            break;
                        case Date:
                            PerformCleanRestorePointsByType(result, secondParameter);
                            break;
                        default:
                            PerformCleanRestorePointsByType(result, thirdParameter);
                            break;
                    }
                }
            }
        }
    }
}