#pragma once

#include "Client.h"

namespace banks::entities
{
    class Bank
    {
    public:
        Bank() = default;
        Bank(std::string name,
             double debitPercent = 0,
             percent_t depositPercent = percent_t(),
             double creditCommission = 0,
             double doubtfulLimit = 0);

        void AddClient(const Client& client);
        [[nodiscard]] std::vector<Client> GetClients() const;

        void SetDebitPercent(double debitPercent);
        void SetDepositPercent(percent_t depositPercent);
        void SetCreditCommission(double creditCommission);
        void SetDoubtfulLimit(double limit);

        void Pay();

        void SetCurrentDate(boost::gregorian::date date);

    private:
        std::string         m_name;
        std::vector<Client> m_clients;
        double              m_debitPercent;
        percent_t           m_depositPercent;
        double              m_creditCommission;
        double              m_doubtfulLimit;
    };
}