#include "Collaborator.h"

namespace reports::entities
{
    Collaborator::Collaborator(std::string name)
        : m_name            ( std::move(name) )
        , m_supervisor      ( nullptr )
        , m_subordinatesList(  )
    {}

    Collaborator::Collaborator(std::string                name,
                               Collaborator*              supervisor,
                               std::vector<Collaborator*> subordinatesList)
        : m_name            ( std::move(name) )
        , m_supervisor      ( supervisor )
        , m_subordinatesList( std::move(subordinatesList) )
    {}

    std::string Collaborator::GetName() const
    {
        return m_name;
    }

    Collaborator* Collaborator::GetSupervisor() const
    {
        return m_supervisor;
    }

    void Collaborator::SetSupervisor(Collaborator* supervisor)
    {
        m_supervisor = supervisor;
    }

    std::vector<Collaborator*> Collaborator::GetSubordinatesList() const
    {
        return m_subordinatesList;
    }

    void Collaborator::SetSubordinatesList(std::vector<Collaborator*>& subordinatesList)
    {
        m_subordinatesList = subordinatesList;
    }
}