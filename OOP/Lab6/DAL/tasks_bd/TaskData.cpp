#include "TaskData.h"

namespace reports::data
{
    TaskData::TaskData()
    {
        Open("tasks.db");
    }

    void TaskData::Init()
    {
        std::string query = "CREATE TABLE IF NOT EXISTS tasks (" \
                                "name TEXT NOT NULL," \
                                "description TEXT NOT NULL," \
                                "assignee BLOB NOT NULL" \
                            ");";
        Execute(query);
    }

    void TaskData::AddTask(const std::string& name,
                           const std::string& description,
                           Collaborator*      assignee)
    {
        std::string query = "INSERT INTO tasks ('name', 'description', 'assignee') VALUES ('";
        query += name;
        query += "', '";
        query += description;
        query += "', '";
        query += reinterpret_cast<const char*>(assignee);
        query += "');";
        Execute(query);
    }

    TaskSystem TaskData::GetAllData()
    {
        std::string query = "SELECT * FROM tasks;";
        Execute(query);
        return TaskSystem();
    }
}