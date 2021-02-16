#pragma once

#include "Transaction.h"

#include <variant>
#include <vector>

namespace banks::entities
{
    class AccountManager : public Transactions
    {
    public:
        void AddAccount(Account* account);

        Account* GetAccountByID(accountID_t id);
        [[nodiscard]] std::vector<Account*> GetAccounts() const;

        transactionID_t Withdraw (accountID_t id, double amount) final;
        transactionID_t Replenish(accountID_t id, double amount) final;
        transactionID_t Transfer (accountID_t idFrom, accountID_t idTo, double amount) final;

        void Cancel(transactionID_t id) final;

    private:
        std::vector<Account*> m_accounts;
    };
}