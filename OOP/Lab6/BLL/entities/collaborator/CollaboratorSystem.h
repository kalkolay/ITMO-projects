#pragma once

#include "Collaborator.h"

#include <map>

namespace reports::entities
{
    class CollaboratorSystem
    {
    public:
        void AddCollaborator(Collaborator* collaborator);
        void SetSupervisor(Collaborator* collaborator, Collaborator* supervisor);

        Collaborator* GetCollaboratorByName(const std::string& name);
        [[nodiscard]] Collaborator* GetTeamLead() const;

        // Key: supervisor, Value: list of subordinates
        [[nodiscard]] std::multimap<Collaborator*, std::vector<Collaborator*>> GetHierarchy() const;

        Collaborator* operator [](unsigned index);

    private:
        std::vector<Collaborator*> m_collaborators;
    };
}
