#include "ReportPerDay.h"

#include "../../exceptions/UnfamiliarTaskException.h"
#include "../../exceptions/UnresolvedTaskException.h"
#include "../../exceptions/OverdueReportException.h"

namespace reports::entities
{
    using namespace reports::exceptions;

    ReportPerDay::ReportPerDay(std::string   name,
                               Collaborator* author)
        : m_name        ( std::move(name) )
        , m_author      ( author )
        , m_creationTime( std::chrono::system_clock::now() )
    {}

    std::string ReportPerDay::GetName() const
    {
        return m_name;
    }

    std::string ReportPerDay::GetText() const
    {
        return m_text;
    }

    Collaborator* ReportPerDay::GetAuthor() const
    {
        return m_author;
    }

    std::vector<Task*> ReportPerDay::GetTasks() const
    {
        return m_tasks.GetTasks();
    }

    bool ReportPerDay::IsOverdue() const
    {
        return std::chrono::system_clock::now() <= m_creationTime + std::chrono::hours(24);
    }

    void ReportPerDay::SetText(std::string text)
    {
        if ( IsOverdue() )
            throw OverdueReportException("Error: cannot modify overdue daily report");
        m_text = std::move(text);
    }

    void ReportPerDay::AddTask(Task* task)
    {
        if ( IsOverdue() )
            throw OverdueReportException("Impossible to add the task to overdue daily report");
        if (task->GetAssignee() != m_author)
            throw UnfamiliarTaskException("Impossible to add someone else's task to your daily report");
        if (task->GetStatus() != k_Resolved)
            throw UnresolvedTaskException("Impossible to add unresolved task to daily report");
        m_tasks.AddTask(task);
    }
}