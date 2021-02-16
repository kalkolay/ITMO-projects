#pragma once

#include "../BLL/entities/task/TaskSystem.h"

namespace reports::ui
{
    using namespace reports::entities;

    class TaskManager
    {
    public:
        TaskManager() = default;

        TaskManager(const TaskManager&)             = delete;
        TaskManager& operator =(const TaskManager&) = delete;

        void AddTask();

        void SetAssignee();
        void SetStatus  ();
        void AddComment ();

        void PrintTasks();

        [[nodiscard]] Task* GetTaskByID                    () const;
        [[nodiscard]] Task* GetTaskByName                  () const;
        [[nodiscard]] Task* GetTaskByLastModifyDate        () const;
        [[nodiscard]] Task* GetTaskByAssignee              () const;
        [[nodiscard]] Task* GetTaskByLastModifyCollaborator() const;

        [[nodiscard]] std::vector<Task*> GetTaskListBySubordinate() const;

    private:
        TaskSystem m_tasks;
    };
}