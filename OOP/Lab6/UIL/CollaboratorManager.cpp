#include "CollaboratorManager.h"

#include <iostream>

namespace reports::ui
{
    void CollaboratorManager::AddCollaborator()
    {
        std::cout << "Adding a new collaborator:\n";
        std::cout << "\tEnter collaborator's name: ";
        std::string name;
        std::getline(std::cin, name);
        auto* collaborator = new Collaborator(name);
        m_collaborators.AddCollaborator(collaborator);
    }

    void CollaboratorManager::SetSupervisor()
    {
        std::cout << "Setting a supervisor:\n";
        std::cout << "\tEnter collaborator's name: ";
        std::string collaboratorName;
        std::getline(std::cin, collaboratorName);
        std::cout << "\tEnter supervisor's name: ";
        std::string supervisorName;
        std::getline(std::cin, supervisorName);
        Collaborator* collaborator = m_collaborators.GetCollaboratorByName(collaboratorName);
        Collaborator* supervisor   = m_collaborators.GetCollaboratorByName(supervisorName);
        if (collaborator == nullptr || supervisor == nullptr)
        {
            std::cerr << "The entered collaborator or supervisor does not exist.";
            return;
        }
        m_collaborators.SetSupervisor(collaborator, supervisor);
    }

    void CollaboratorManager::PrintHierarchy()
    {
        std::cout << "Current hierarchy of collaborators:\n";
        auto hierarchy = m_collaborators.GetHierarchy();
        int position = 1;
        for (const auto& i : hierarchy)
        {
            std::cout << '\t' << position << ". Supervisor: " << i.first->GetName() << ". Subordinates: ";
            if ( !i.second.empty() )
            {
                for (auto subordinate : i.second)
                    std::cout << subordinate->GetName() << '\t';
            }
            else
            {
                std::cout << "none";
            }
            std::cout << std::endl;
            ++position;
        }
    }
}