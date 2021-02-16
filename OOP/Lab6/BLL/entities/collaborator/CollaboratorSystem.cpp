#include "CollaboratorSystem.h"

namespace reports::entities
{
    void CollaboratorSystem::AddCollaborator(Collaborator* collaborator)
    {
        m_collaborators.push_back(collaborator);
    }

    void CollaboratorSystem::SetSupervisor(Collaborator* collaborator, Collaborator* supervisor)
    {
        for (auto currentCollaborator : m_collaborators)
            if (currentCollaborator == collaborator)
            {
                currentCollaborator->SetSupervisor(supervisor);
                break;
            }
    }

    Collaborator* CollaboratorSystem::GetCollaboratorByName(const std::string& name)
    {
        for (auto currentCollaborator : m_collaborators)
            if (currentCollaborator->GetName() == name)
                return currentCollaborator;
        return nullptr;
    }

    Collaborator* CollaboratorSystem::GetTeamLead() const
    {
        for (auto currentCollaborator : m_collaborators)
            if (currentCollaborator->GetSupervisor() == nullptr)
                return currentCollaborator;
        return nullptr;
    }

    std::multimap<Collaborator*, std::vector<Collaborator*>> CollaboratorSystem::GetHierarchy() const
    {
        std::multimap<Collaborator*, std::vector<Collaborator*>> hierarchy;
        for (auto currentCollaborator : m_collaborators)
            hierarchy.insert( { currentCollaborator->GetSupervisor(),
                                currentCollaborator->GetSubordinatesList() } );
        return hierarchy;
    }

    Collaborator* CollaboratorSystem::operator [](unsigned index)
    {
        return m_collaborators[index];
    }
}