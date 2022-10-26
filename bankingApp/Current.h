#pragma once
#include "Account.h"
class Current : public Account
{
private:
    double overdraft; // has to be >= -500

public:
    Current(double _balance);
    ~Current();
    void deposit(double value);
    std::string toString();
    void withdraw(double value);
};
