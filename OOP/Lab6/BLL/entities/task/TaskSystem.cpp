#include "TaskSystem.h"

#include <algorithm>

namespace reports::entities
{
    void TaskSystem::AddTask(Task* task)
    {
        m_tasks.push_back(task);
    }

    void TaskSystem::AddTask(std::string   name,
                             std::string   description,
                             Collaborator* assignee)
    {
        Task task(std::move(name), std::move(description), assignee);
        m_tasks.push_back(&task);
    }

    std::vector<Task*> TaskSystem::GetTasks() const
    {
        return m_tasks;
    }

    Task* TaskSystem::GetTaskByID(taskID_t id) const
    {
        auto it = std::find_if(m_tasks.begin(), m_tasks.end(),
                               [=](Task* task){ return task->GetID() == id; });
        return it == m_tasks.end() ? nullptr : *it;
    }

    Task* TaskSystem::GetTaskByName(const std::string& name) const
    {
        auto it = std::find_if(m_tasks.begin(), m_tasks.end(),
                               [=](Task* task){ return task->GetName() == name; });
        return it == m_tasks.end() ? nullptr : *it;
    }

    Task* TaskSystem::GetTaskByLastModifyDate(clock_t time) const
    {
        auto it = std::find_if(m_tasks.begin(), m_tasks.end(),
                               [=](Task* task){ return task->GetLastModifyTime() == time; });
        return it == m_tasks.end() ? nullptr : *it;
    }

    Task* TaskSystem::GetTaskByAssignee(Collaborator* assignee) const
    {
        auto it = std::find_if(m_tasks.begin(), m_tasks.end(),
                               [=](Task* task){ return task->GetAssignee() == assignee; });
        return it == m_tasks.end() ? nullptr : *it;
    }

    Task* TaskSystem::GetTaskByLastModifyCollaborator(Collaborator* collaborator) const
    {
        auto it = std::find_if(m_tasks.begin(), m_tasks.end(),
                               [=](Task* task){ return task->GetLastModifyCollaborator() == collaborator; });
        return it == m_tasks.end() ? nullptr : *it;
    }

    std::vector<Task*> TaskSystem::GetTaskListBySubordinate(Collaborator* supervisor) const
    {
        std::vector<Task*> resultTasks;
        for (auto currentTask : m_tasks)
            if (currentTask->GetAssignee()->GetSupervisor() == supervisor)
                resultTasks.push_back(currentTask);
        return resultTasks;
    }
}
