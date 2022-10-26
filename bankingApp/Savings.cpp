#include "Savings.h"
#include <cmath>

Savings::Savings(bool _isa, double _balance)
{
    // Sets private attributes
    isa = _isa;
    setBalance(_balance);
    // creates transaction to add to history
    Transaction t("initial deposit", _balance);
    pushHistory(t);
    // Differnt intrest rates for savings and ISA
    if (_isa == true)
    {
        // 1.15%
        intrestRate = 0.0115;
    }
    else
    {
        intrestRate = 0.0085;
    } // 0.85%
}

// Savings::~Savings() { std::cout << "Savings destroyed"; }
Savings::~Savings() {} // destructor

void Savings::deposit(double value)
{
    // adds value to balance
    addBalance(value);
    std::cout << toString() << std::endl;
    // creates transaction and adds to history
    Transaction t("deposit", value);
    pushHistory(t);
}

void Savings::withdraw(double value)
{
    if ((getBalance() - value) >= 0.00)
    {
        // takes value away from balance
        addBalance(-value);
        std::cout << toString() << std::endl;
        // creates transaction and adds to history
        Transaction t("withdraw", value);
        pushHistory(t);
    }
    else
    {
        std::cout << "Balance too low, transaction would put balance in negative" << std::endl;
    }
}

/// <summary>
/// Creates an output message
/// </summary>
/// <returns>		output message		</returns>
std::string Savings::toString()
{
    std::string s;
    if (isa == true)
    {
        s = "ISA | Balance: \x9C" + std::to_string(getBalance());
    }
    else
    {
        s = "Savings | Balance: \x9C" + std::to_string(getBalance());
    }
    return s;
}

// Need to check maths
/*
Order in BIDMAS
A = P(1 + r/n)^nt
1) (1 + r/n) has to be done first
2) next is result ^ nt
3) this result * balance

*/

/// <summary>
/// Computes intrest using a formula
/// </summary>
/// <param name="years">		years in future		</param>
void Savings::computeIntrest(int years)
{
    if (years > 0)
    {
        // A = P(1+r/n)^nt
        double finalAmount;
        double working = (1 + (intrestRate / 12));
        working = pow(working, (12 * years));
        finalAmount = getBalance() * working;
        std::cout << "Projected balance: \x9C" << finalAmount << std::endl;
    }
    else
    {
        std::cout << "Can't project a negative value" << std::endl;
    }
}