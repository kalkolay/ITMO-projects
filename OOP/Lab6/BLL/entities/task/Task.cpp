#include "Task.h"

namespace reports::entities
{
    Task::Task(std::string   name,
               std::string   description,
               Collaborator* assignee)
        : m_name                  ( std::move(name) )
        , m_description           ( std::move(description) )
        , m_assignee              ( assignee )
        , m_status                ( k_Open )
        , m_lastModifyTime        ( std::chrono::system_clock::now() )
        , m_lastModifyCollaborator( assignee )
    {
        boost::uuids::random_generator uuid_gen;
        m_id = uuid_gen();
    }

    std::string Task::GetName() const
    {
        return m_name;
    }

    std::string Task::GetDescription() const
    {
        return m_description;
    }

    Collaborator* Task::GetAssignee() const
    {
        return m_assignee;
    }

    ETaskStatus Task::GetStatus() const
    {
        return m_status;
    }

    taskID_t Task::GetID() const
    {
        return m_id;
    }

    std::vector<TaskComment*> Task::GetComments() const
    {
        return m_comments;
    }

    clock_t Task::GetLastModifyTime() const
    {
        return m_lastModifyTime;
    }

    Collaborator* Task::GetLastModifyCollaborator() const
    {
        return m_lastModifyCollaborator;
    }

    void Task::SetAssignee(Collaborator* currentCollaborator,
                           Collaborator* assignee)
    {
        m_assignee               = assignee;
        m_lastModifyTime         = std::chrono::system_clock::now();
        m_lastModifyCollaborator = currentCollaborator;
    }

    void Task::SetStatus(Collaborator* currentCollaborator,
                         ETaskStatus status)
    {
        m_status                 = status;
        m_lastModifyTime         = std::chrono::system_clock::now();
        m_lastModifyCollaborator = currentCollaborator;
    }

    void Task::AddComment(TaskComment* comment)
    {
        m_comments.push_back(comment);
        m_lastModifyTime         = std::chrono::system_clock::now();
        m_lastModifyCollaborator = comment->GetAuthor();
    }
}