#pragma once

#include "../BLL/entities/collaborator/CollaboratorSystem.h"

namespace reports::ui
{
    using namespace reports::entities;

    class CollaboratorManager
    {
    public:
        CollaboratorManager() = default;

        CollaboratorManager(const CollaboratorManager&)             = delete;
        CollaboratorManager& operator =(const CollaboratorManager&) = delete;

        void AddCollaborator();
        void SetSupervisor  ();

        void PrintHierarchy();

    private:
        CollaboratorSystem m_collaborators;
    };
}