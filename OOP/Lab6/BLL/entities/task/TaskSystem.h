#pragma once

#include "Task.h"

namespace reports::entities
{
    class TaskSystem
    {
    public:
        void AddTask(Task* task);
        void AddTask(std::string   name,
                     std::string   description,
                     Collaborator* assignee);

        [[nodiscard]] std::vector<Task*> GetTasks() const;

        [[nodiscard]] Task* GetTaskByID                    (taskID_t id)                const;
        [[nodiscard]] Task* GetTaskByName                  (const std::string& name)    const;
        [[nodiscard]] Task* GetTaskByLastModifyDate        (clock_t time)               const;
        [[nodiscard]] Task* GetTaskByAssignee              (Collaborator* assignee)     const;
        [[nodiscard]] Task* GetTaskByLastModifyCollaborator(Collaborator* collaborator) const;

        [[nodiscard]] std::vector<Task*> GetTaskListBySubordinate(Collaborator* supervisor) const;

    private:
        std::vector<Task*> m_tasks;
    };
}