#include <iostream>
#include "Account.h"

Account::~Account() {} // destructor

void Account::addBalance(double value)
{
    balance += value;
}

double Account::getBalance()
{
    return balance;
}

void Account::setBalance(double _balance)
{
    balance = _balance;
}
std::vector<Transaction> Account::getHistory()
{
    return history;
}
void Account::pushHistory(Transaction t)
{
    history.push_back(t);
}