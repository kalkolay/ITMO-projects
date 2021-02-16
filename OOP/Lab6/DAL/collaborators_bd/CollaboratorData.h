#pragma once

#include "../Data.h"
#include "../../BLL/entities/collaborator/CollaboratorSystem.h"

namespace reports::data
{
    using namespace reports::entities;

    class CollaboratorData : public Data
    {
    public:
        CollaboratorData();

        CollaboratorData(const CollaboratorData&)             = delete;
        CollaboratorData& operator =(const CollaboratorData&) = delete;

        void Init() override;

        void AddCollaborator(const std::string&                name,
                             Collaborator*                     supervisor,
                             const std::vector<Collaborator*>& subordinates);

        [[nodiscard]] CollaboratorSystem GetAllData();
    };
}
