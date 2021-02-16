#pragma once

#include "AbsoluteRestorePoint.h"
#include "IncrementalRestorePoint.h"

#include <boost/uuid/uuid.hpp>
#include <boost/uuid/random_generator.hpp>
#include <boost/uuid/uuid_io.hpp>

#include <list>
#include <variant>
#include <any>

namespace backup::entities
{
    using uuid_t        = boost::uuids::uuid;
    using RestorePoint  = std::variant<AbsoluteRestorePoint, IncrementalRestorePoint>;
    using RestorePoints = std::list<RestorePoint>;

    enum ETypeStorage
    {
        Separate,
        Common
    };

    enum ETypeCleaning
    {
        Number,
        Date,
        Size,
        None
    };

    class Backup
    {
    public:
        Backup();
        explicit Backup(const Files& files);

        [[nodiscard]] uuid_t         GetId           () const;
        [[nodiscard]] std::string    GetCreationTime () const;
        [[nodiscard]] std::uintmax_t GetSize         () const;
        [[nodiscard]] RestorePoints  GetRestorePoints() const;
        [[nodiscard]] Files          GetFiles        () const;

        void AddFile   (const FileInfo& file);
        void RemoveFile(const FileInfo& file);

        void CreateAbsoluteRestorePoint(ETypeStorage algorithm);
        void DeleteAbsoluteRestorePoint(const AbsoluteRestorePoint& restorePoint);
        void CreateIncrementalRestorePoint(IncrementalRestorePoint* prevPoint,
                                           ETypeStorage             algorithm);
        void DeleteIncrementalRestorePoint(const IncrementalRestorePoint& restorePoint);

        void CleanRestorePointsByNumber(unsigned           number);
        void CleanRestorePointsByDate  (const std::string& date);
        void CleanRestorePointsBySize  (std::uintmax_t     size);
        void CleanRestorePointsHybrid  (bool            cleanIfAllFail,
                                        ETypeCleaning   firstAlgorithm,
                                        const std::any& firstParameter,
                                        ETypeCleaning   secondAlgorithm,
                                        const std::any& secondParameter,
                                        ETypeCleaning   thirdAlgorithm = ETypeCleaning::None,
                                        const std::any& thirdParameter = -1);

    private:
        uuid_t         m_id;
        std::string    m_creationTime;
        std::uintmax_t m_size;
        RestorePoints  m_restorePoints;
        Files          m_files;

        void PerformStorageAlgorithm(ETypeStorage algorithm);

        unsigned CleanRestorePointsByNumberCount(unsigned           number);
        unsigned CleanRestorePointsByDateCount  (const std::string& date);
        unsigned CleanRestorePointsBySizeCount  (std::uintmax_t     size);
        unsigned CleanRestorePointsCount        (ETypeCleaning   algorithm,
                                                 const std::any& parameter);
        void     PerformCleanRestorePointsByType(ETypeCleaning   algorithm,
                                                 const std::any& parameter);
    };
}