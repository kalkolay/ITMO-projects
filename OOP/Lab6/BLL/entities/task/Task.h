#pragma once

#include "TaskComment.h"

#include <chrono>

#include <boost/uuid/uuid.hpp>
#include <boost/uuid/random_generator.hpp>
#include <boost/uuid/uuid_io.hpp>

namespace reports::entities
{
    enum ETaskStatus
    {
        k_Open,
        k_Active,
        k_Resolved
    };

    using taskID_t = boost::uuids::uuid;
    using clock_t  = std::chrono::system_clock::time_point;

    class Task
    {
    public:
        Task(std::string   name,
             std::string   description,
             Collaborator* assignee);

        [[nodiscard]] std::string               GetName                  () const;
        [[nodiscard]] std::string               GetDescription           () const;
        [[nodiscard]] Collaborator*             GetAssignee              () const;
        [[nodiscard]] ETaskStatus               GetStatus                () const;
        [[nodiscard]] taskID_t                  GetID                    () const;
        [[nodiscard]] std::vector<TaskComment*> GetComments              () const;
        [[nodiscard]] clock_t                   GetLastModifyTime        () const;
        [[nodiscard]] Collaborator*             GetLastModifyCollaborator() const;

        void SetAssignee(Collaborator* currentCollaborator,
                         Collaborator* assignee);
        void SetStatus  (Collaborator* currentCollaborator,
                         ETaskStatus   status);

        void AddComment(TaskComment* comment);

    private:
        taskID_t                  m_id;
        std::string               m_name;
        std::string               m_description;
        Collaborator*             m_assignee;
        ETaskStatus               m_status;
        std::vector<TaskComment*> m_comments;
        clock_t                   m_lastModifyTime;
        Collaborator*             m_lastModifyCollaborator;
    };
}