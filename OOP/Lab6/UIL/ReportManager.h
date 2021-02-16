#pragma once

#include "../BLL/entities/report/ReportPerDay.h"
#include "../BLL/entities/report/ReportPerSprint.h"
#include "../BLL/entities/report/CommandReport.h"

namespace reports::ui
{
    using namespace reports::entities;

    class ReportManager
    {
    public:
        ReportManager() = default;

        ReportManager(const ReportManager&)             = delete;
        ReportManager& operator =(const ReportManager&) = delete;

        void CreateDailyReport  ();
        void CreateSprintReport ();
        void CreateCommandReport();

        /// Daily Report
        [[nodiscard]] std::string        GetDailyReportName  () const;
        [[nodiscard]] std::string        GetDailyReportText  () const;
        [[nodiscard]] Collaborator*      GetDailyReportAuthor() const;
        [[nodiscard]] std::vector<Task*> GetDailyReportTasks () const;

        [[nodiscard]] bool IsDailyReportOverdue() const;

        void SetDailyReportText();
        void AddDailyReportTask();

        /// Sprint Report
        [[nodiscard]] std::string                   GetSprintReportName                    () const;
        [[nodiscard]] std::string                   GetSprintReportText                    () const;
        [[nodiscard]] Collaborator*                 GetSprintReportAuthor                  () const;
        [[nodiscard]] clock_t                       GetSprintReportDeadline                () const;
        [[nodiscard]] std::vector<Task*>            GetSprintReportTasks                   () const;
        [[nodiscard]] std::vector<ReportPerDay*>    GetSprintReportDailyReports            () const;
        [[nodiscard]] std::vector<ReportPerSprint*> GetSprintReportSubordinateSprintReports() const;

        [[nodiscard]] bool GetIsSprintReportClosed() const;
        [[nodiscard]] bool IsSprintReportOverdue  () const;

        void SetSprintReportText    ();
        void SetIsSprintReportClosed();

        void AddDailyReportToSprintReport                ();
        void AddSubordinateSprintReportToMainSprintReport();

        /// Command Report
        [[nodiscard]] std::string                   GetCommandReportName         () const;
        [[nodiscard]] std::string                   GetCommandReportText         () const;
        [[nodiscard]] Collaborator*                 GetCommandReportAuthor       () const;
        [[nodiscard]] std::vector<Task*>            GetCommandReportTasks        () const;
        [[nodiscard]] std::vector<ReportPerSprint*> GetCommandReportSprintReports() const;

        void SetCommandReportText();

        void AddSprintReportToCommandReport();

    private:
        std::vector<ReportPerDay*>    m_dailyReports;
        std::vector<ReportPerSprint*> m_sprintReports;
        std::vector<CommandReport*>   m_commandReports;
    };
}