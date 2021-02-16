#pragma once

#include "../task/TaskSystem.h"

namespace reports::entities
{
    class ReportPerDay
    {
    public:
        ReportPerDay(std::string   name,
                     Collaborator* author);

        [[nodiscard]] std::string        GetName  () const;
        [[nodiscard]] std::string        GetText  () const;
        [[nodiscard]] Collaborator*      GetAuthor() const;
        [[nodiscard]] std::vector<Task*> GetTasks () const;

        [[nodiscard]] bool IsOverdue() const;

        void SetText(std::string text);
        void AddTask(Task* task);

    private:
        std::string        m_name;
        std::string        m_text;
        Collaborator*      m_author;
        TaskSystem         m_tasks;
        clock_t            m_creationTime;
    };
}