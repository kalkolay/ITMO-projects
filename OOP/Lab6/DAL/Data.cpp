#include "Data.h"

namespace reports::data
{
    Data::~Data()
    {
        Close();
    }

    void Data::Open(const std::string& name)
    {
        m_resultCode = sqlite3_open(name.c_str(), &m_db);
        if (m_resultCode)
            throw std::runtime_error( sqlite3_errmsg(m_db) );
    }

    void Data::Close()
    {
        sqlite3_close(m_db);
    }

    void Data::Execute(const std::string& query)
    {
        m_resultCode = sqlite3_exec(m_db, query.c_str(), callback, nullptr, &m_errMsg);
    }
}