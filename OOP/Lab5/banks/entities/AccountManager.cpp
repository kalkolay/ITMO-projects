#include "AccountManager.h"

namespace banks::entities
{
    void AccountManager::AddAccount(Account* account)
    {
        m_accounts.push_back(account);
    }

    Account* AccountManager::GetAccountByID(accountID_t id)
    {
        for (auto account : m_accounts)
            if (account->GetID() == id)
                return account;
        return nullptr;
    }

    std::vector<Account*> AccountManager::GetAccounts() const
    {
        return m_accounts;
    }

    transactionID_t AccountManager::Withdraw(accountID_t id, double amount)
    {
        Transaction newTransaction(k_Withdraw, amount, id);
        AddTransaction(newTransaction);

        Account* tmp = GetAccountByID(id);
        if ( typeid(*tmp) == typeid(CreditAccount) )
        {
            double newAmount = tmp->GetCurrentAmount() - amount;
            tmp->SetCurrentAmount(newAmount);
        }
        else if ( typeid(*tmp) == typeid(DebitAccount) )
        {
            double newAmount = tmp->GetCurrentAmount() - amount;
            if (newAmount < 0)
            {
                return transactionID_t();
            }
            else
            {
                tmp->SetCurrentAmount(newAmount);
            }
        }
        else if ( typeid(*tmp) == typeid(Deposit) )
        {
            Deposit tmpDeposit = reinterpret_cast<Deposit&&>(tmp);
            if ( tmpDeposit.GetIsExpired() )
            {
                return transactionID_t();
            }
            else
            {
                double newAmount = tmpDeposit.GetCurrentAmount() - amount;
                if (newAmount < 0)
                {
                    return transactionID_t();
                }
                else
                {
                    tmpDeposit.SetCurrentAmount(newAmount);
                }
            }
        }
        else
        {
            return transactionID_t();
        }

        return newTransaction.GetID();
    }

    transactionID_t AccountManager::Replenish(accountID_t id, double amount)
    {
        Transaction newTransaction(k_Replenish, amount, id);
        AddTransaction(newTransaction);

        Account* tmp = GetAccountByID(id);
        tmp->SetCurrentAmount(tmp->GetCurrentAmount() + amount);

        return newTransaction.GetID();
    }

    transactionID_t AccountManager::Transfer(accountID_t idFrom, accountID_t idTo, double amount)
    {
        Transaction newTransaction(k_Transfer, amount, idFrom, idTo);
        AddTransaction(newTransaction);

        Withdraw(idFrom, amount);
        Replenish(idTo, amount);

        return newTransaction.GetID();
    }

    void AccountManager::Cancel(transactionID_t id)
    {
        Transaction tmp = GetTransactionByID(id);
        transactionID_t backTransactionID;
        switch ( tmp.GetType() )
        {
            case k_Withdraw:
                backTransactionID = Replenish( tmp.GetAccountID().first, tmp.GetAmount() );
                break;
            case k_Replenish:
                backTransactionID = Withdraw( tmp.GetAccountID().first, tmp.GetAmount() );
                break;
            case k_Transfer:
                backTransactionID = Transfer( tmp.GetAccountID().second, tmp.GetAccountID().first, tmp.GetAmount() );
                break;
            default:
                break;
        }
        RemoveTransaction(id);
        RemoveTransaction(backTransactionID);
    }
}