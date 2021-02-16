#include "CreditAccount.h"

namespace banks::entities
{
    CreditAccount::CreditAccount(double commission)
        : m_commission(commission)
    {
        Initialize();
    }

    void CreditAccount::SetCommission(double commission)
    {
        m_commission = commission;
    }

    void CreditAccount::CalculateDailyPayment()
    {
        SetFrozenAmount( GetFrozenAmount() - GetCurrentAmount() * m_commission / 36500 );
    }
}