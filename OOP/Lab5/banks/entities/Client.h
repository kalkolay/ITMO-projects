#pragma once

#include "AccountManager.h"

#include <string>

namespace banks::entities
{
    class Client
    {
    public:
        Client(std::string firstName, std::string lastName);

        void SetAddress(std::string address);
        void SetPassport(std::string passport);

        [[nodiscard]] bool GetIsDoubtful() const;

        [[nodiscard]] std::vector<Account*> GetAccounts() const;
        [[nodiscard]] AccountManager        GetAccountManager() const;

        void CreateDebitAccount ();
        void CreateDeposit      ();
        void CreateCreditAccount();

    private:
        std::string    m_firstName;
        std::string    m_lastName;
        std::string    m_address;
        std::string    m_passport;
        bool           m_isDoubtful;
        AccountManager m_accounts;
    };
}