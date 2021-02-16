#include "CollaboratorData.h"

#include "../Utilities.h"

namespace reports::data
{
    using namespace reports::data::utils;

    std::string ConvertSubordinatesToXML(const std::vector<Collaborator*>& subordinates)
    {
        std::vector<std::string> tmp;
        tmp.reserve( subordinates.size() );
        for (auto elem : subordinates)
            tmp.emplace_back( reinterpret_cast<const char*>(elem) );
        return SerializeFromVectorToXML(tmp);
    }

    CollaboratorData::CollaboratorData()
    {
        Open("collaborators.db");
    }

    void CollaboratorData::Init()
    {
        std::string query = "CREATE TABLE IF NOT EXISTS collaborators (" \
                                "name TEXT NOT NULL," \
                                "supervisor BLOB," \
                                "subordinates TEXT" \
                            ");";
        Execute(query);
    }

    void CollaboratorData::AddCollaborator(const std::string&                name,
                                           Collaborator*                     supervisor,
                                           const std::vector<Collaborator*>& subordinates)
    {
        std::string query = "INSERT INTO collaborators ('name', 'supervisor', 'subordinates') VALUES ('";
        query += name;
        query += "', '";
        query += reinterpret_cast<const char*>(supervisor);
        query += "', '";
        query += ConvertSubordinatesToXML(subordinates);
        query += "');";
        Execute(query);
    }

    CollaboratorSystem CollaboratorData::GetAllData()
    {
        std::string query = "SELECT * FROM collaborators;";
        Execute(query);
        return CollaboratorSystem();
    }
}