#pragma once

#include "ReportPerSprint.h"

namespace reports::entities
{
    class CommandReport
    {
    public:
        CommandReport(std::string   name,
                      Collaborator* author);

        [[nodiscard]] std::string                   GetName         () const;
        [[nodiscard]] std::string                   GetText         () const;
        [[nodiscard]] Collaborator*                 GetAuthor       () const;
        [[nodiscard]] std::vector<Task*>            GetTasks        () const;
        [[nodiscard]] std::vector<ReportPerSprint*> GetSprintReports() const;

        void SetText(std::string text);

        void AddSprintReport(ReportPerSprint* report);

    private:
        std::string                   m_name;
        std::string                   m_text;
        Collaborator*                 m_teamLead;
        std::vector<ReportPerSprint*> m_reports;

        [[nodiscard]] bool IsAuthorTeamLead() const;
    };
}