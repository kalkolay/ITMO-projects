#include "banks/entities/Bank.h"

#define ACCOUNT(num) bank.GetClients()[num].GetAccountManager()

using namespace banks::entities;

double DepositPercent(double startAmount)
{
    if (startAmount < 500)
        return 3;
    else if (startAmount >= 500 && startAmount < 1000)
        return 3.5;
    else
        return 4;
}

int main()
{
    Bank bank("Тинькофф", 3.65, DepositPercent, 3.65, 1000);

    Client client1("Николай", "Федотенко");
    client1.SetAddress("ул. Пушкина, д. Колотушкина");
    client1.SetPassport("1488 228322");
    client1.CreateCreditAccount();

    Client client2("Олег", "Тиньков");
    client2.CreateDebitAccount();

    Client client3("Алина", "Зябликова");
    client3.SetAddress("Италия");
    client3.CreateDebitAccount();

    bank.AddClient(client1);
    ACCOUNT(0).GetAccounts()[0]->SetCurrentAmount(5000);
    bank.AddClient(client2);
    ACCOUNT(1).GetAccounts()[0]->SetCurrentAmount(1000000);
    bank.AddClient(client3);
    ACCOUNT(2).GetAccounts()[0]->SetCurrentAmount(100);

    ACCOUNT(2).Replenish(ACCOUNT(2).GetAccounts()[0]->GetID(), 1000);

    bank.SetCurrentDate( boost::gregorian::day_clock::local_day() + boost::gregorian::months(1) );
    bank.Pay();

    return 0;
}
