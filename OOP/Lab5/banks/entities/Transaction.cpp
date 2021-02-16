#include "Transaction.h"

namespace banks::entities
{
    Transaction::Transaction(ETransactionType type, double amount, accountID_t idFrom, accountID_t idTo)
    {
        SetID();
        SetType(type);
        SetAmount(amount);
        SetAccountID(idFrom, idTo);
    }

    transactionID_t Transaction::GetID() const
    {
        return m_id;
    }

    void Transaction::SetID()
    {
        boost::uuids::random_generator uuid_gen;
        m_id = uuid_gen();
    }

    ETransactionType Transaction::GetType() const
    {
        return m_lastTransactionType;
    }

    void Transaction::SetType(ETransactionType type)
    {
        m_lastTransactionType = type;
    }

    double Transaction::GetAmount() const
    {
        return m_amount;
    }

    void Transaction::SetAmount(double amount)
    {
        m_amount = amount;
    }

    std::pair<accountID_t, accountID_t> Transaction::GetAccountID() const
    {
        return m_lastAccountID;
    }

    void Transaction::SetAccountID(accountID_t idFrom, accountID_t idTo)
    {
        m_lastAccountID.first  = idFrom;
        m_lastAccountID.second = idTo;
    }

    transactionID_t Transaction::Withdraw(accountID_t id, double amount)
    {
        return transactionID_t();
    }

    transactionID_t Transaction::Replenish(accountID_t id, double amount)
    {
        return transactionID_t();
    }

    transactionID_t Transaction::Transfer(accountID_t idFrom, accountID_t idTo, double amount)
    {
        return transactionID_t();
    }

    Transaction Transactions::GetTransactionByID(transactionID_t id)
    {
        if ( m_transactions.find(id) != m_transactions.end() )
            return m_transactions[id];
        return Transaction();
    }

    void Transactions::AddTransaction(const Transaction& transaction)
    {
        m_transactions[transaction.GetID()] = transaction;
    }

    void Transactions::RemoveTransaction(transactionID_t id)
    {
        m_transactions.erase(id);
    }

    void Transactions::Cancel(transactionID_t id) {}
}