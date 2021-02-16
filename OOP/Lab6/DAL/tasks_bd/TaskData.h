#pragma once

#include "../Data.h"
#include "../../BLL/entities/task/TaskSystem.h"

namespace reports::data
{
    using namespace reports::entities;

    class TaskData : public Data
    {
    public:
        TaskData();

        TaskData(const TaskData&)             = delete;
        TaskData& operator =(const TaskData&) = delete;

        void Init() override;

        void AddTask(const std::string& name,
                     const std::string& description,
                     Collaborator*      assignee);

        [[nodiscard]] TaskSystem GetAllData();
    };
}