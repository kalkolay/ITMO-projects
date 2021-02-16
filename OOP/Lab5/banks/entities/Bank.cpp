#include "Bank.h"

#include <utility>

namespace banks::entities
{
    Bank::Bank(std::string name,
               double debitPercent,
               percent_t depositPercent,
               double creditCommission,
               double doubtfulLimit)
        : m_name            ( std::move(name) )
        , m_debitPercent    ( debitPercent )
        , m_depositPercent  ( std::move(depositPercent) )
        , m_creditCommission( creditCommission )
        , m_doubtfulLimit   ( doubtfulLimit )
    {}

    void Bank::AddClient(const Client& client)
    {
        m_clients.push_back(client);
    }

    void Bank::SetDebitPercent(double debitPercent)
    {
        m_debitPercent = debitPercent;
    }

    void Bank::SetDepositPercent(percent_t depositPercent)
    {
        m_depositPercent = std::move(depositPercent);
    }

    void Bank::SetCreditCommission(double creditCommission)
    {
        m_creditCommission = creditCommission;
    }

    void Bank::SetDoubtfulLimit(double limit)
    {
        m_doubtfulLimit = limit;
    }

    void Bank::Pay()
    {
        for (const auto& client : m_clients)
            for ( auto account : client.GetAccounts() )
                account->Pay();
    }

    void Bank::SetCurrentDate(boost::gregorian::date date)
    {
        for (const auto& client : m_clients)
            for ( auto account : client.GetAccounts() )
                account->SetCurrentDate(date);
    }

    std::vector<Client> Bank::GetClients() const
    {
        return m_clients;
    }
}