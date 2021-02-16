#pragma once

#include <iostream>
#include <string>

#include <sqlite3.h>

namespace reports::data
{
    class Data
    {
    public:
        virtual ~Data();

        void Open (const std::string& name);
        void Close();

        virtual void Init() {}

        void Execute(const std::string& query);

    private:
        sqlite3*    m_db;
        int         m_resultCode;
        char*       m_errMsg = nullptr;

        /// Callback for SQLite queries execution
        static int callback(void* NotUsed, int argc, char** argv, char** azColName)
        {
            // int argc:          holds the number of results
            // (array) azColName: holds each column returned
            // (array) argv:      holds each value
            for (int i = 0; i < argc; ++i)
                std::cout << azColName[i] << ": " << argv[i] << std::endl;
            std::cout << std::endl;
            return 0;
        }
    };
}