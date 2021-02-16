#include "ReportData.h"

#include "../Utilities.h"

namespace reports::data
{
    using namespace reports::data::utils;

    ReportData::ReportData()
    {
        Open("reports.db");
    }

    void ReportData::Init()
    {
        std::string query = "CREATE TABLE IF NOT EXISTS reports (" \
                                "type TEXT NOT NULL," \
                                "name TEXT NOT NULL," \
                                "author BLOB NOT NULL," \
                                "deadline BLOB," \
                                "report BLOB BOT NULL"
                            ");";    // type: "daily", "sprint", "command"
        Execute(query);
    }

    void ReportData::AddDailyReport(ReportPerDay* report)
    {
        std::string query = "INSERT INTO reports ('type', 'name', 'author', 'report') VALUES ('";
        query += "daily', '";
        query += report->GetName();
        query += "', '";
        query += reinterpret_cast<const char*>( report->GetAuthor() );
        query += "', '";
        query += reinterpret_cast<const char*>(report);
        query += "');";
        Execute(query);
        m_dailyReports.push_back(report);
    }

    void ReportData::AddSprintReport(ReportPerSprint* report)
    {
        std::string query = "INSERT INTO reports ('type', 'name', 'author', 'deadline', 'report') VALUES ('";
        query += "sprint', '";
        query += report->GetName();
        query += "', '";
        query += reinterpret_cast<const char*>( report->GetAuthor() );
        query += "', '";
        query += time_to_string( report->GetDeadline() );
        query += "', '";
        query += reinterpret_cast<const char*>(report);
        query += "');";
        Execute(query);
        m_sprintReports.push_back(report);
    }

    void ReportData::AddCommandReport(CommandReport* report)
    {
        std::string query = "INSERT INTO reports ('type', 'name', 'author', 'report') VALUES ('";
        query += "command', '";
        query += report->GetName();
        query += "', '";
        query += reinterpret_cast<const char*>( report->GetAuthor() );
        query += "', '";
        query += reinterpret_cast<const char*>(report);
        query += "');";
        Execute(query);
        m_commandReports.push_back(report);
    }

    ReportPerDay* ReportData::GetDailyReportData(unsigned index)
    {
        std::string query = "SELECT report FROM reports WHERE rowid = ";
        query += std::to_string(index);
        query += " AND type LIKE '%daily%';";
        Execute(query);
        return nullptr;
    }

    ReportPerSprint* ReportData::GetSprintReportData(unsigned index)
    {
        std::string query = "SELECT report FROM reports WHERE rowid = ";
        query += std::to_string(index);
        query += " AND type LIKE '%sprint%';";
        Execute(query);
        return nullptr;
    }

    CommandReport* ReportData::GetCommandReportData(unsigned index)
    {
        std::string query = "SELECT report FROM reports WHERE rowid = ";
        query += std::to_string(index);
        query += " AND type LIKE '%command%';";
        Execute(query);
        return nullptr;
    }
}