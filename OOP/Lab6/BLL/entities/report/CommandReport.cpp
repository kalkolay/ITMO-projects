#include "CommandReport.h"

#include "../../exceptions/UnfamiliarReportException.h"

namespace reports::entities
{
    using namespace reports::exceptions;

    CommandReport::CommandReport(std::string   name,
                                 Collaborator* author)
        : m_name    ( std::move(name) )
        , m_teamLead( author )
    {}

    std::string CommandReport::GetName() const
    {
        return m_name;
    }

    std::string CommandReport::GetText() const
    {
        return m_text;
    }

    Collaborator* CommandReport::GetAuthor() const
    {
        return m_teamLead;
    }

    std::vector<Task*> CommandReport::GetTasks() const
    {
        std::vector<Task*> resultTasks;
        for (auto report : m_reports)
            for (auto task : report->GetTasks())
                resultTasks.push_back(task);
        return resultTasks;
    }

    std::vector<ReportPerSprint*> CommandReport::GetSprintReports() const
    {
        return m_reports;
    }

    void CommandReport::SetText(std::string text)
    {
        if ( IsAuthorTeamLead() )
            m_text = std::move(text);
        else
            throw UnfamiliarReportException("Error: only team lead is able to modify command report");
    }

    void CommandReport::AddSprintReport(ReportPerSprint* report)
    {
        if ( IsAuthorTeamLead() )
            m_reports.push_back(report);
        else
            throw UnfamiliarReportException("Error: only team lead is able to modify command report");
    }

    bool CommandReport::IsAuthorTeamLead() const
    {
        return m_teamLead->GetSupervisor() == nullptr;
    }
}