#pragma once

#include "Account.h"

namespace banks::entities
{
    class CreditAccount : public Account
    {
    public:
        explicit CreditAccount(double commission = 0);

        [[nodiscard]] double GetCommission() const { return m_commission; }

        void CalculateDailyPayment() override;

    private:
        double m_commission;

        void SetCommission(double commission);
    };
}