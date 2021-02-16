#pragma once

#include "ReportPerDay.h"

namespace reports::entities
{
    class ReportPerSprint
    {
    public:
        ReportPerSprint(std::string   name,
                        Collaborator* author,
                        clock_t       deadline);

        [[nodiscard]] std::string                   GetName                    () const;
        [[nodiscard]] std::string                   GetText                    () const;
        [[nodiscard]] Collaborator*                 GetAuthor                  () const;
        [[nodiscard]] clock_t                       GetDeadline                () const;
        [[nodiscard]] std::vector<Task*>            GetTasks                   () const;
        [[nodiscard]] std::vector<ReportPerDay*>    GetDailyReports            () const;
        [[nodiscard]] std::vector<ReportPerSprint*> GetSubordinateSprintReports() const;

        [[nodiscard]] bool GetIsClosed() const;
        [[nodiscard]] bool IsOverdue  () const;

        void SetText    (std::string text);
        void SetIsClosed(bool status);

        void AddDailyReport            (ReportPerDay* report);
        void AddSubordinateSprintReport(ReportPerSprint* report);

    private:
        std::string                   m_name;
        std::string                   m_text;
        Collaborator*                 m_author;
        clock_t                       m_deadline;
        bool                          m_isClosed;
        std::vector<ReportPerDay*>    m_reports;
        std::vector<ReportPerSprint*> m_subordinateReports;
        clock_t                       m_creationTime;
    };
}