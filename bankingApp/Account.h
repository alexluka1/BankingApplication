#pragma once
#include <vector>
#include <iostream>
#include "Transaction.h"

/// <summary>
/// Abstract class to create all accounts from
/// </summary>
class Account
{
private:
    double balance;
    std::vector<Transaction> history;

public:
    virtual ~Account();

    virtual void deposit(double value) = 0;
    virtual void withdraw(double value) = 0;
    virtual std::string toString() = 0;

    // accessors and mutators are needed to manipulate in derived classes.
    double getBalance();
    void addBalance(double amount);
    void setBalance(double _balance);
    std::vector<Transaction> getHistory();
    void pushHistory(Transaction t);
};