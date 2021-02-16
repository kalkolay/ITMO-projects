#include "TaskManager.h"

#include <iostream>
#include <iomanip>

#include <boost/lexical_cast.hpp>

namespace reports::ui
{
    std::time_t str_to_time(const std::string& tp)
    {
        struct std::tm tm{};
        std::istringstream ss(tp);
        ss >> std::get_time(&tm, "%A, %d %B %Y %H:%M");
        return mktime(&tm);
    }

    void TaskManager::AddTask()
    {
        std::cout << "Adding a new task:\n";
        std::cout << "\tEnter task's name: ";
        std::string name;
        std::getline(std::cin, name);
        std::cout << "\tEnter task's description: ";
        std::string description;
        std::getline(std::cin, description);
        std::cout << "\tEnter the name of task's assignee: ";
        std::string assigneeName;
        std::getline(std::cin, assigneeName);
        auto* assignee = new Collaborator(assigneeName);
        m_tasks.AddTask(name, description, assignee);
    }

    void TaskManager::SetAssignee()
    {
        std::cout << "Setting a new assignee:\n";
        std::cout << "\tEnter task's name: ";
        std::string taskName;
        std::getline(std::cin, taskName);
        std::cout << "\tEnter current collaborator's name: ";
        std::string currentCollaboratorName;
        std::getline(std::cin, currentCollaboratorName);
        std::cout << "\tEnter new assignee's name: ";
        std::string newAssigneeName;
        std::getline(std::cin, newAssigneeName);
        Task* task = m_tasks.GetTaskByName(taskName);
        auto* currentCollaborator = new Collaborator(currentCollaboratorName);
        auto* newAssignee         = new Collaborator(newAssigneeName);
        task->SetAssignee(currentCollaborator, newAssignee);
    }

    void TaskManager::SetStatus()
    {
        std::cout << "Setting a new status:\n";
        std::cout << "\tEnter task's name: ";
        std::string taskName;
        std::getline(std::cin, taskName);
        std::cout << "\tEnter current collaborator's name: ";
        std::string currentCollaboratorName;
        std::getline(std::cin, currentCollaboratorName);
        std::cout << "\tEnter new status (Open, Active, or Resolved): ";
        std::string strStatus;
        std::getline(std::cin, strStatus);
        Task* task = m_tasks.GetTaskByName(taskName);
        auto* currentCollaborator = new Collaborator(currentCollaboratorName);
        ETaskStatus newStatus;
        if (strStatus == "Open")
            newStatus = k_Open;
        else if (strStatus == "Active")
            newStatus = k_Active;
        else if (strStatus == "Resolved")
            newStatus = k_Resolved;
        else
        {
            std::cerr << "Error: Wrong status." << std::endl;
            return;
        }
        task->SetStatus(currentCollaborator, newStatus);
    }

    void TaskManager::AddComment()
    {
        std::cout << "Adding a comment:\n";
        std::cout << "\tEnter task's name: ";
        std::string taskName;
        std::getline(std::cin, taskName);
        std::cout << "\tEnter author's name: ";
        std::string authorName;
        std::getline(std::cin, authorName);
        std::cout << "\tEnter the comment's text: ";
        std::string commentText;
        std::getline(std::cin, commentText);
        Task* task = m_tasks.GetTaskByName(taskName);
        auto* author  = new Collaborator(authorName);
        auto* comment = new TaskComment(author, commentText);
        task->AddComment(comment);
    }

    void TaskManager::PrintTasks()
    {
        std::cout << "Current task list:\n";
        int position = 1;
        for ( auto task : m_tasks.GetTasks() )
            std::cout << '\t' << position << ". Name: " << task->GetName()
                      << ". Description: " << task->GetDescription()
                      << ". Assignee: " << task->GetAssignee() << std::endl;
    }

    Task* TaskManager::GetTaskByID() const
    {
        std::cout << "Getting task by its ID:\n";
        std::cout << "\tEnter task's ID: ";
        std::string strTaskID;
        std::getline(std::cin, strTaskID);
        auto taskID = boost::lexical_cast<taskID_t>(strTaskID);
        Task* ans = m_tasks.GetTaskByID(taskID);
        std::cout << "Returning task with given ID: " << ans->GetName() << std::endl;
        return ans;
    }

    Task* TaskManager::GetTaskByName() const
    {
        std::cout << "Getting task by its name:\n";
        std::cout << "\tEnter task's name: ";
        std::string taskName;
        std::getline(std::cin, taskName);
        Task* ans = m_tasks.GetTaskByName(taskName);
        std::cout << "Returning task with given name: " << ans->GetName() << std::endl;
        return ans;
    }

    Task* TaskManager::GetTaskByLastModifyDate() const
    {
        std::cout << "Getting task by its latest modify time:\n";
        std::cout << "\tEnter task's latest modify time: ";
        std::string strTaskLastModifyDate;
        std::getline(std::cin, strTaskLastModifyDate);
        auto taskLastModifyDate = std::chrono::system_clock::from_time_t( str_to_time(strTaskLastModifyDate) );
        Task* ans = m_tasks.GetTaskByLastModifyDate(taskLastModifyDate);
        std::cout << "Returning task with given latest modify time: " << ans->GetName() << std::endl;
        return ans;
    }

    Task* TaskManager::GetTaskByAssignee() const
    {
        std::cout << "Getting task by its assignee:\n";
        std::cout << "\tEnter the name of the task's assignee: ";
        std::string strTaskAssigneeName;
        std::getline(std::cin, strTaskAssigneeName);
        auto* assignee = new Collaborator(strTaskAssigneeName);
        Task* ans = m_tasks.GetTaskByAssignee(assignee);
        std::cout << "Returning task with given assignee's name: " << ans->GetName() << std::endl;
        return ans;
    }

    Task* TaskManager::GetTaskByLastModifyCollaborator() const
    {
        std::cout << "Getting task by the latest modified collaborator:\n";
        std::cout << "\tEnter the name of the task's latest modified collaborator: ";
        std::string strTaskLastModifyCollaboratorName;
        std::getline(std::cin, strTaskLastModifyCollaboratorName);
        auto* collaborator = new Collaborator(strTaskLastModifyCollaboratorName);
        Task* ans = m_tasks.GetTaskByLastModifyCollaborator(collaborator);
        std::cout << "Returning task with given latest modified collaborator's name: "
                  << ans->GetName() << std::endl;
        return ans;
    }

    std::vector<Task*> TaskManager::GetTaskListBySubordinate() const
    {
        std::cout << "Getting task list by supervisor's name:\n";
        std::cout << "\tEnter the name of the supervisor: ";
        std::string strTaskSupervisorName;
        std::getline(std::cin, strTaskSupervisorName);
        auto* supervisor = new Collaborator(strTaskSupervisorName);
        std::vector<Task*> ans = m_tasks.GetTaskListBySubordinate(supervisor);
        std::cout << "Returning task list with given supervisor's name: ";
        for (auto collaborator : ans)
            std::cout << '\t' << collaborator->GetName();
        std::cout << std::endl;
        return ans;
    }
}