#pragma once

#include "Account.h"

#include <chrono>
#include <functional>

namespace banks::entities
{
    using percent_t    = std::function<double(double)>;
    using time_point_t = std::chrono::system_clock::time_point;

    class Deposit : public Account
    {
    public:
        explicit Deposit(percent_t percent = nullptr);

        void SetDeadline(time_point_t deadline);

        [[nodiscard]] bool GetIsExpired() const;

        void CalculateDailyPayment() override;

    private:
        percent_t    m_percent;
        time_point_t m_deadline;

        void SetPercent(percent_t percent);
    };
}