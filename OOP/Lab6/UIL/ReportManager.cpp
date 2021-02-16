#include "ReportManager.h"

#include <iostream>
#include <iomanip>
#include <sstream>

namespace reports::ui
{
    std::time_t string_to_time(const std::string& tp)
    {
        struct std::tm tm{};
        std::istringstream ss(tp);
        ss >> std::get_time(&tm, "%A, %d %B %Y %H:%M");
        return mktime(&tm);
    }

    void ReportManager::CreateDailyReport()
    {
        std::cout << "Creating a daily report:\n";
        std::cout << "\tEnter report's name: ";
        std::string reportName;
        std::getline(std::cin, reportName);
        std::cout << "\tEnter author's name: ";
        std::string authorName;
        std::getline(std::cin, authorName);
        auto* author = new Collaborator(authorName);
        auto* report = new ReportPerDay(reportName, author);
        m_dailyReports.push_back(report);
    }

    void ReportManager::CreateSprintReport()
    {
        std::cout << "Creating a sprint report:\n";
        std::cout << "\tEnter report's name: ";
        std::string reportName;
        std::getline(std::cin, reportName);
        std::cout << "\tEnter author's name: ";
        std::string authorName;
        std::getline(std::cin, authorName);
        std::cout << "\tEnter the deadline time: ";
        std::string strDeadline;
        std::getline(std::cin, strDeadline);
        auto* author = new Collaborator(authorName);
        clock_t deadline = std::chrono::system_clock::from_time_t( string_to_time(strDeadline) );
        auto* report = new ReportPerSprint(reportName, author, deadline);
        m_sprintReports.push_back(report);
    }

    void ReportManager::CreateCommandReport()
    {
        std::cout << "Creating a command report:\n";
        std::cout << "\tEnter report's name: ";
        std::string reportName;
        std::getline(std::cin, reportName);
        std::cout << "\tEnter author's name (must be the team lead): ";
        std::string authorName;
        std::getline(std::cin, authorName);
        auto* author = new Collaborator(authorName);
        auto* report = new CommandReport(reportName, author);
        m_commandReports.push_back(report);
    }

    /// Daily Report

    std::string ReportManager::GetDailyReportName() const
    {
        std::cout << "Enter daily report's index: ";
        unsigned index;
        std::cin >> index;
        std::string retVal = m_dailyReports[index]->GetName();
        std::cout << "Returning daily report's " << index << " name: " << retVal << std::endl;
        return retVal;
    }

    std::string ReportManager::GetDailyReportText() const
    {
        std::cout << "Enter daily report's index: ";
        unsigned index;
        std::cin >> index;
        std::string retVal = m_dailyReports[index]->GetText();
        std::cout << "Returning daily report's " << index << " text: " << retVal << std::endl;
        return retVal;
    }

    Collaborator* ReportManager::GetDailyReportAuthor() const
    {
        std::cout << "Enter daily report's index: ";
        unsigned index;
        std::cin >> index;
        Collaborator* retVal = m_dailyReports[index]->GetAuthor();
        std::cout << "Returning daily report's " << index << " author: " << retVal << std::endl;
        return retVal;
    }

    std::vector<Task*> ReportManager::GetDailyReportTasks() const
    {
        std::cout << "Enter daily report's index: ";
        unsigned index;
        std::cin >> index;
        std::vector<Task*> retVal = m_dailyReports[index]->GetTasks();
        std::cout << "Returning daily report's " << index << " tasks: ";
        for (auto task : retVal)
            std::cout << '\t' << task->GetName();
        std::cout << std::endl;
        return retVal;
    }

    bool ReportManager::IsDailyReportOverdue() const
    {
        std::cout << "Enter daily report's index: ";
        unsigned index;
        std::cin >> index;
        bool retVal = m_dailyReports[index]->IsOverdue();
        std::cout << std::boolalpha << "Returning if daily report " << index
                  << " is overdue: " << retVal << std::endl;
        return retVal;
    }

    void ReportManager::SetDailyReportText()
    {
        std::cout << "Enter daily report's index: ";
        unsigned index;
        std::cin >> index;
        std::cout << "Enter new daily report's text: ";
        std::string reportText;
        std::getline(std::cin, reportText);
        m_dailyReports[index]->SetText(reportText);
        std::cout << "New daily report's text is successfully set." << std::endl;
    }

    void ReportManager::AddDailyReportTask()
    {
        std::cout << "Enter daily report's index: ";
        unsigned index;
        std::cin >> index;
        std::cout << "Enter new daily report task's name: ";
        std::string taskName;
        std::getline(std::cin, taskName);
        std::cout << "Enter new daily report task's description: ";
        std::string taskDescription;
        std::getline(std::cin, taskDescription);
        std::cout << "Enter new daily report task's author: ";
        std::string taskAuthor;
        std::getline(std::cin, taskAuthor);
        auto* author = new Collaborator(taskAuthor);
        auto* task = new Task(taskName, taskDescription, author);
        m_dailyReports[index]->AddTask(task);
        std::cout << "New daily report's task is successfully added." << std::endl;
    }

    /// Sprint Report

    std::string ReportManager::GetSprintReportName() const
    {
        std::cout << "Enter sprint report's index: ";
        unsigned index;
        std::cin >> index;
        std::string retVal = m_sprintReports[index]->GetName();
        std::cout << "Returning sprint report's " << index << " name: " << retVal << std::endl;
        return retVal;
    }

    std::string ReportManager::GetSprintReportText() const
    {
        std::cout << "Enter sprint report's index: ";
        unsigned index;
        std::cin >> index;
        std::string retVal = m_sprintReports[index]->GetText();
        std::cout << "Returning sprint report's " << index << " text: " << retVal << std::endl;
        return retVal;
    }

    Collaborator* ReportManager::GetSprintReportAuthor() const
    {
        std::cout << "Enter sprint report's index: ";
        unsigned index;
        std::cin >> index;
        Collaborator* retVal = m_sprintReports[index]->GetAuthor();
        std::cout << "Returning sprint report's " << index
                  << " author: " << retVal->GetName() << std::endl;
        return retVal;
    }

    clock_t ReportManager::GetSprintReportDeadline() const
    {
        std::cout << "Enter sprint report's index: ";
        unsigned index;
        std::cin >> index;
        clock_t retVal = m_sprintReports[index]->GetDeadline();
        std::cout << "Returning sprint report's " << index << " deadline: "
                  << std::ctime( (time_t*)std::chrono::system_clock::to_time_t(retVal) ) << std::endl;
        return retVal;
    }

    std::vector<Task*> ReportManager::GetSprintReportTasks() const
    {
        std::cout << "Enter sprint report's index: ";
        unsigned index;
        std::cin >> index;
        std::vector<Task*> retVal = m_sprintReports[index]->GetTasks();
        std::cout << "Returning sprint report's " << index << " tasks: ";
        for (auto task : retVal)
            std::cout << '\t' << task->GetName();
        std::cout << std::endl;
        return retVal;
    }

    std::vector<ReportPerDay*> ReportManager::GetSprintReportDailyReports() const
    {
        std::cout << "Enter sprint report's index: ";
        unsigned index;
        std::cin >> index;
        std::vector<ReportPerDay*> retVal = m_sprintReports[index]->GetDailyReports();
        std::cout << "Returning sprint report's " << index << " daily reports: ";
        for (auto dailyReport : retVal)
            std::cout << '\t' << dailyReport->GetName();
        std::cout << std::endl;
        return retVal;
    }

    std::vector<ReportPerSprint*> ReportManager::GetSprintReportSubordinateSprintReports() const
    {
        std::cout << "Enter sprint report's index: ";
        unsigned index;
        std::cin >> index;
        std::vector<ReportPerSprint*> retVal = m_sprintReports[index]->GetSubordinateSprintReports();
        std::cout << "Returning sprint report's " << index << " subordinate sprint reports: ";
        for (auto sprintReport : retVal)
            std::cout << '\t' << sprintReport->GetName();
        std::cout << std::endl;
        return retVal;
    }

    bool ReportManager::GetIsSprintReportClosed() const
    {
        std::cout << "Enter sprint report's index: ";
        unsigned index;
        std::cin >> index;
        bool retVal = m_sprintReports[index]->GetIsClosed();
        std::cout << std::boolalpha << "Returning if sprint report " << index
                  << " is closed: " << retVal << std::endl;
        return retVal;
    }

    bool ReportManager::IsSprintReportOverdue() const
    {
        std::cout << "Enter sprint report's index: ";
        unsigned index;
        std::cin >> index;
        bool retVal = m_sprintReports[index]->IsOverdue();
        std::cout << std::boolalpha << "Returning if sprint report " << index
                  << " is overdue: " << retVal << std::endl;
        return retVal;
    }

    void ReportManager::SetSprintReportText()
    {
        std::cout << "Enter sprint report's index: ";
        unsigned index;
        std::cin >> index;
        std::cout << "Enter new sprint report's text: ";
        std::string reportText;
        std::getline(std::cin, reportText);
        m_sprintReports[index]->SetText(reportText);
        std::cout << "New sprint report's text is successfully set." << std::endl;
    }

    void ReportManager::SetIsSprintReportClosed()
    {
        std::cout << "Enter sprint report's index: ";
        unsigned index;
        std::cin >> index;
        std::cout << "Enter new sprint report's status (0 - opened, 1 - closed): ";
        std::string reportStatus;
        std::getline(std::cin, reportStatus);
        bool status = false;
        if (reportStatus == "0")
            status = false;
        else if (reportStatus == "1")
            status = true;
        else
        {
            std::cerr << "Error: wrong status typed." << std::endl;
            return;
        }
        m_sprintReports[index]->SetIsClosed(status);
        std::cout << "New sprint report's status is successfully set." << std::endl;
    }

    void ReportManager::AddDailyReportToSprintReport()
    {
        std::cout << "Enter sprint report's index: ";
        unsigned index;
        std::cin >> index;
        std::cout << "Enter new daily report's name: ";
        std::string dailyReportName;
        std::getline(std::cin, dailyReportName);
        std::cout << "Enter new daily report's author: ";
        std::string dailyReportAuthor;
        std::getline(std::cin, dailyReportAuthor);
        auto* author = new Collaborator(dailyReportAuthor);
        auto* dailyReport = new ReportPerDay(dailyReportName, author);
        m_sprintReports[index]->AddDailyReport(dailyReport);
        std::cout << "New daily report is successfully added." << std::endl;
    }

    void ReportManager::AddSubordinateSprintReportToMainSprintReport()
    {
        std::cout << "Enter sprint report's index: ";
        unsigned index;
        std::cin >> index;
        std::cout << "Enter new subordinate sprint report's name: ";
        std::string subordinateSprintReportName;
        std::getline(std::cin, subordinateSprintReportName);
        std::cout << "Enter new subordinate sprint report's author: ";
        std::string subordinateSprintReportAuthor;
        std::getline(std::cin, subordinateSprintReportAuthor);
        std::cout << "Enter new subordinate sprint report's deadline: ";
        std::string subordinateSprintReportDeadline;
        std::getline(std::cin, subordinateSprintReportAuthor);
        auto* author  = new Collaborator(subordinateSprintReportAuthor);
        auto deadline = std::chrono::system_clock::from_time_t( string_to_time(subordinateSprintReportDeadline) );
        auto* sprintReport = new ReportPerSprint(subordinateSprintReportName, author, deadline);
        m_sprintReports[index]->AddSubordinateSprintReport(sprintReport);
        std::cout << "New subordinate sprint report is successfully added." << std::endl;
    }

    /// Command Report

    std::string ReportManager::GetCommandReportName() const
    {
        std::cout << "Enter command report's index: ";
        unsigned index;
        std::cin >> index;
        std::string retVal = m_commandReports[index]->GetName();
        std::cout << "Returning command report's " << index << " name: " << retVal << std::endl;
        return retVal;
    }

    std::string ReportManager::GetCommandReportText() const
    {
        std::cout << "Enter command report's index: ";
        unsigned index;
        std::cin >> index;
        std::string retVal = m_commandReports[index]->GetText();
        std::cout << "Returning command report's " << index << " text: " << retVal << std::endl;
        return retVal;
    }

    Collaborator* ReportManager::GetCommandReportAuthor() const
    {
        std::cout << "Enter command report's index: ";
        unsigned index;
        std::cin >> index;
        Collaborator* retVal = m_commandReports[index]->GetAuthor();
        std::cout << "Returning command report's " << index << " author: " << retVal->GetName() << std::endl;
        return retVal;
    }

    std::vector<Task*> ReportManager::GetCommandReportTasks() const
    {
        std::cout << "Enter command report's index: ";
        unsigned index;
        std::cin >> index;
        std::vector<Task*> retVal = m_commandReports[index]->GetTasks();
        std::cout << "Returning command report's " << index << " tasks: ";
        for (auto task : retVal)
            std::cout << '\t' << task->GetName();
        std::cout << std::endl;
        return retVal;
    }

    std::vector<ReportPerSprint*> ReportManager::GetCommandReportSprintReports() const
    {
        std::cout << "Enter command report's index: ";
        unsigned index;
        std::cin >> index;
        std::vector<ReportPerSprint*> retVal = m_commandReports[index]->GetSprintReports();
        std::cout << "Returning command report's " << index << " sprint reports: ";
        for (auto sprintReport : retVal)
            std::cout << '\t' << sprintReport->GetName();
        std::cout << std::endl;
        return retVal;
    }

    void ReportManager::SetCommandReportText()
    {
        std::cout << "Enter command report's index: ";
        unsigned index;
        std::cin >> index;
        std::cout << "Enter new command report's text: ";
        std::string reportText;
        std::getline(std::cin, reportText);
        m_commandReports[index]->SetText(reportText);
        std::cout << "New command report's text is successfully set." << std::endl;
    }

    void ReportManager::AddSprintReportToCommandReport()
    {
        std::cout << "Enter command report's index: ";
        unsigned index;
        std::cin >> index;
        std::cout << "Enter new sprint report's name: ";
        std::string sprintReportName;
        std::getline(std::cin, sprintReportName);
        std::cout << "Enter new sprint report's author: ";
        std::string sprintReportAuthor;
        std::getline(std::cin, sprintReportAuthor);
        std::cout << "Enter new sprint report's deadline: ";
        std::string sprintReportDeadline;
        std::getline(std::cin, sprintReportDeadline);
        auto* author  = new Collaborator(sprintReportAuthor);
        auto deadline = std::chrono::system_clock::from_time_t( string_to_time(sprintReportDeadline) );
        auto* sprintReport = new ReportPerSprint(sprintReportName, author, deadline);
        m_commandReports[index]->AddSprintReport(sprintReport);
        std::cout << "New sprint report is successfully added." << std::endl;
    }
}