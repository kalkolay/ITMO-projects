#include "Deposit.h"

#include <utility>

namespace banks::entities
{
    Deposit::Deposit(percent_t percent)
        : m_percent  ( std::move(percent) )
    {
        Initialize();
    }

    void Deposit::SetPercent(percent_t percent)
    {
        m_percent = std::move(percent);
    }

    void Deposit::SetDeadline(time_point_t deadline)
    {
        m_deadline = deadline;
    }

    bool Deposit::GetIsExpired() const
    {
        return std::chrono::system_clock::now() >= m_deadline;
    }

    void Deposit::CalculateDailyPayment()
    {
        SetFrozenAmount(GetFrozenAmount() + GetCurrentAmount() * m_percent( GetCurrentAmount() ) / 36500);
    }
}