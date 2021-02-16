#pragma once

#include "../Data.h"
#include "../../BLL/entities/report/CommandReport.h"

namespace reports::data
{
    using namespace reports::entities;

    class ReportData : public Data
    {
    public:
        ReportData();

        ReportData(const ReportData&)             = delete;
        ReportData& operator =(const ReportData&) = delete;

        void Init() override;

        void AddDailyReport  (ReportPerDay*    report);
        void AddSprintReport (ReportPerSprint* report);
        void AddCommandReport(CommandReport*   report);

        [[nodiscard]] ReportPerDay*    GetDailyReportData  (unsigned index);
        [[nodiscard]] ReportPerSprint* GetSprintReportData (unsigned index);
        [[nodiscard]] CommandReport*   GetCommandReportData(unsigned index);

    private:
        std::vector<ReportPerDay*>    m_dailyReports;
        std::vector<ReportPerSprint*> m_sprintReports;
        std::vector<CommandReport*>   m_commandReports;
    };
}