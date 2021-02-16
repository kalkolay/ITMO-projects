#include "Client.h"

#include <utility>

namespace banks::entities
{
    Client::Client(std::string firstName, std::string lastName)
        : m_firstName  ( std::move(firstName) )
        , m_lastName   ( std::move(lastName) )
        , m_address    ( "" )
        , m_passport   ( "" )
        , m_isDoubtful ( true )
    {}

    void Client::SetAddress(std::string address)
    {
        m_address = std::move(address);
        if ( !m_address.empty() && !m_passport.empty() )
            m_isDoubtful = false;
    }

    void Client::SetPassport(std::string passport)
    {
        m_passport = std::move(passport);
        if ( !m_address.empty() && !m_passport.empty() )
            m_isDoubtful = false;
    }

    bool Client::GetIsDoubtful() const
    {
        return m_isDoubtful;
    }

    std::vector<Account*> Client::GetAccounts() const
    {
        return m_accounts.GetAccounts();
    }

    AccountManager Client::GetAccountManager() const
    {
        return m_accounts;
    }

    void Client::CreateDebitAccount()
    {
        DebitAccount debit;
        m_accounts.AddAccount(&debit);
    }

    void Client::CreateDeposit()
    {
        Deposit deposit;
        m_accounts.AddAccount(&deposit);
    }

    void Client::CreateCreditAccount()
    {
        CreditAccount credit;
        m_accounts.AddAccount(&credit);
    }
}