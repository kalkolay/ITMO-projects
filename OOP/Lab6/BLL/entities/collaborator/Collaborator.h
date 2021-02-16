#pragma once

#include <string>
#include <vector>

namespace reports::entities
{
    class Collaborator
    {
    public:
        explicit Collaborator(std::string name);
        Collaborator(std::string                name,
                     Collaborator*              supervisor,
                     std::vector<Collaborator*> subordinatesList);

        [[nodiscard]] std::string GetName() const;

        [[nodiscard]] Collaborator* GetSupervisor() const;
        void SetSupervisor(Collaborator* supervisor);

        [[nodiscard]] std::vector<Collaborator*> GetSubordinatesList() const;
        void SetSubordinatesList(std::vector<Collaborator*>& subordinatesList);

    private:
        std::string                m_name;
        Collaborator*              m_supervisor;
        std::vector<Collaborator*> m_subordinatesList;
    };
}