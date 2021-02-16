#pragma once

#include "Account.h"

namespace banks::entities
{
    class DebitAccount : public Account
    {
    public:
        explicit DebitAccount(double percent = 0);

        void CalculateDailyPayment() override;

    private:
        double m_percent;

        void SetPercent(double percent);
    };
}