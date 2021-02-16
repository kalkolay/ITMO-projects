#include "Account.h"

namespace banks::entities
{
    Account::Account()
    {
        Initialize();
    }

    accountID_t Account::GetID() const
    {
        return m_id;
    }

    double Account::GetCurrentAmount() const
    {
        return m_currentAmount;
    }

    void Account::SetCurrentAmount(double amount)
    {
        m_currentAmount = amount;
    }

    double Account::GetFrozenAmount() const
    {
        return m_frozenAmount;
    }

    void Account::SetFrozenAmount(double amount)
    {
        m_frozenAmount = amount;
    }

    boost::gregorian::date Account::GetLastPaymentDate() const
    {
        return m_lastPaymentDate;
    }

    boost::gregorian::date Account::GetCurrentDate() const
    {
        return m_currentDate;
    }

    void Account::SetCurrentDate(boost::gregorian::date date)
    {
        m_currentDate = date;
    }

    void Account::SetLastPaymentDate(boost::gregorian::date date)
    {
        m_lastPaymentDate = date;
    }

    void Account::Initialize()
    {
        boost::uuids::random_generator uuid_gen;
        m_id = uuid_gen();
        m_lastPaymentDate = boost::gregorian::day_clock::local_day();
        SetCurrentDate(m_lastPaymentDate);
        SetCurrentAmount(0);
        SetFrozenAmount (0);
    }

    void Account::CalculateDailyPayment() {}

    void Account::Pay()
    {
        size_t daysNumber = (m_currentDate - m_lastPaymentDate).days();
        for (size_t i = 0; i < daysNumber; ++i)
            CalculateDailyPayment();
        SetCurrentAmount( GetCurrentAmount() + GetFrozenAmount() );
        SetFrozenAmount(0);
        SetLastPaymentDate( GetCurrentDate() );
    }
}