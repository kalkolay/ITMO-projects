#pragma once

#include "CreditAccount.h"
#include "DebitAccount.h"
#include "Deposit.h"

#include <map>

namespace banks::entities
{
    using transactionID_t = accountID_t;

    enum ETransactionType
    {
        k_Withdraw,
        k_Replenish,
        k_Transfer
    };

    class Transaction
    {
    public:
        Transaction() = default;
        Transaction( ETransactionType type, double amount, accountID_t idFrom, accountID_t idTo = accountID_t() );

        [[nodiscard]] transactionID_t GetID() const;
        void SetID();

        [[nodiscard]] ETransactionType GetType() const;
        void SetType(ETransactionType type);

        [[nodiscard]] double GetAmount() const;
        void SetAmount(double amount);

        [[nodiscard]] std::pair<accountID_t, accountID_t> GetAccountID() const;
        void SetAccountID( accountID_t idFrom, accountID_t idTo = accountID_t() );

        virtual transactionID_t Withdraw (accountID_t id, double amount);
        virtual transactionID_t Replenish(accountID_t id, double amount);
        virtual transactionID_t Transfer (accountID_t idFrom, accountID_t idTo, double amount);

    private:
        transactionID_t m_id;

        ETransactionType m_lastTransactionType;
        double m_amount;
        std::pair<accountID_t, accountID_t> m_lastAccountID;
    };

    class Transactions : public Transaction
    {
    public:
        Transaction GetTransactionByID(transactionID_t id);

        void AddTransaction(const Transaction& transaction);
        void RemoveTransaction(transactionID_t id);

        virtual void Cancel(transactionID_t id);

    private:
        std::map<transactionID_t, Transaction> m_transactions;
    };
}