#pragma once

#include <boost/uuid/uuid.hpp>
#include <boost/uuid/random_generator.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/date_time/gregorian/gregorian.hpp>

namespace banks::entities
{
    using accountID_t = boost::uuids::uuid;

    class Account
    {
    public:
        Account();
        virtual ~Account() = default;

        [[nodiscard]] accountID_t GetID() const;

        [[nodiscard]] double      GetCurrentAmount() const;
        void                      SetCurrentAmount(double amount);

        [[nodiscard]] double      GetFrozenAmount() const;
        void                      SetFrozenAmount(double amount);

        [[nodiscard]] boost::gregorian::date GetLastPaymentDate() const;
        [[nodiscard]] boost::gregorian::date GetCurrentDate() const;
        void SetLastPaymentDate(boost::gregorian::date date);
        void SetCurrentDate(boost::gregorian::date date);

        void Pay();

    private:
        accountID_t            m_id;
        double                 m_currentAmount;
        double                 m_frozenAmount;
        boost::gregorian::date m_lastPaymentDate;
        boost::gregorian::date m_currentDate;

    protected:
        void Initialize();

        virtual void CalculateDailyPayment();
    };
}