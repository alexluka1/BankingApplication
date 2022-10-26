#pragma once
#include "Account.h"
#include "IntrestEarning.h"

class Savings : public Account,
                public IntrestEarning
{
private:
    // bool isa will be set to true if it is an isa
    bool isa;
    double intrestRate;

public:
    Savings(bool _isa, double _balance);
    ~Savings();
    void deposit(double value);
    void withdraw(double value);
    std::string toString();
    void computeIntrest(int years);
};
