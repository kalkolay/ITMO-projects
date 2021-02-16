#include "DebitAccount.h"

namespace banks::entities
{
    DebitAccount::DebitAccount(double percent)
        : m_percent(percent)
    {
        Initialize();
    }

    void DebitAccount::SetPercent(double percent)
    {
        m_percent = percent;
    }

    void DebitAccount::CalculateDailyPayment()
    {
        SetFrozenAmount(GetFrozenAmount() + GetCurrentAmount() * m_percent / 36500);
    }
}