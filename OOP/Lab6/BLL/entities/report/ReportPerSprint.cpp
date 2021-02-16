#include "ReportPerSprint.h"

#include "../../exceptions/OverdueReportException.h"
#include "../../exceptions/UnfamiliarReportException.h"

#include <algorithm>

namespace reports::entities
{
    using namespace reports::exceptions;

    ReportPerSprint::ReportPerSprint(std::string   name,
                                     Collaborator* author,
                                     clock_t       deadline)
        : m_name        ( std::move(name) )
        , m_author      ( author )
        , m_creationTime( std::chrono::system_clock::now() )
        , m_isClosed    ( false )
    {
        if (deadline >= m_creationTime)
            m_deadline = deadline;
        else
            m_isClosed = true;
    }

    std::string ReportPerSprint::GetName() const
    {
        return m_name;
    }

    std::string ReportPerSprint::GetText() const
    {
        return m_text;
    }

    Collaborator* ReportPerSprint::GetAuthor() const
    {
        return m_author;
    }

    clock_t ReportPerSprint::GetDeadline() const
    {
        return m_deadline;
    }

    std::vector<Task*> ReportPerSprint::GetTasks() const
    {
        std::vector<Task*> resultTasks;
        for (auto report : m_reports)
            for (auto task : report->GetTasks())
                resultTasks.push_back(task);
        return resultTasks;
    }

    std::vector<ReportPerDay*> ReportPerSprint::GetDailyReports() const
    {
        return m_reports;
    }

    std::vector<ReportPerSprint*> ReportPerSprint::GetSubordinateSprintReports() const
    {
        return m_subordinateReports;
    }

    bool ReportPerSprint::GetIsClosed() const
    {
        return m_isClosed;
    }

    bool ReportPerSprint::IsOverdue() const
    {
        return std::chrono::system_clock::now() >= m_deadline;
    }

    void ReportPerSprint::SetText(std::string text)
    {
        if ( IsOverdue() || GetIsClosed() )
            throw OverdueReportException("Error: cannot modify closed sprint report");
        m_text = std::move(text);
    }

    void ReportPerSprint::SetIsClosed(bool status)
    {
        m_isClosed = status;
        if ( IsOverdue() )
            m_isClosed = true;
    }

    void ReportPerSprint::AddDailyReport(ReportPerDay* report)
    {
        if ( IsOverdue() || GetIsClosed() )
            throw OverdueReportException("Impossible to add the task to closed sprint report");
        if (report->GetAuthor() != m_author)
        {
            std::vector<Collaborator*> subordinates = report->GetAuthor()->GetSubordinatesList();
            if ( std::all_of(subordinates.begin(), subordinates.end(),
                             [=](Collaborator* subordinate){ return subordinate != report->GetAuthor(); }) )
                throw UnfamiliarReportException("Impossible to add someone else's daily report to your sprint report");
        }
        m_reports.push_back(report);
    }

    void ReportPerSprint::AddSubordinateSprintReport(ReportPerSprint* report)
    {
        if ( IsOverdue() || GetIsClosed() )
            throw OverdueReportException("Impossible to add the task to closed sprint report");
        std::vector<Collaborator*> subordinates = report->GetAuthor()->GetSubordinatesList();
        auto it = std::find_if(subordinates.begin(), subordinates.end(),
                               [=](Collaborator* subordinate){ return subordinate == report->GetAuthor(); });
        if ( it == subordinates.end() )
            throw UnfamiliarReportException("Impossible to add someone else's report to subordinate sprint report");
        else
            m_subordinateReports.push_back( reinterpret_cast<ReportPerSprint* const>(*it) );
    }
}