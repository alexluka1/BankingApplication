#include "Current.h"

/// <summary>
/// Constructor to initialise attributes
/// </summary>
/// <param name="_balance">		balance to set		</param>
Current::Current(double _balance)
{
    overdraft = 500.00;
    setBalance(_balance);
    Transaction t("initial deposit", _balance);
    pushHistory(t);
}

// Current::~Current(){ std::cout << "Current account destroyed" << std::endl; }
Current::~Current() {} // destructor

void Current::deposit(double value)
{
    // adds value to balance
    addBalance(value);
    std::cout << toString() << std::endl;
    // creates transaction to add to history
    Transaction t("deposit", value);
    pushHistory(t);
}

std::string Current::toString()
{
    std::string s;
    s = "Current | Balance: \x9C" + std::to_string(getBalance());
    return s;
}

void Current::withdraw(double value)
{
    if ((getBalance() - value) >= -500.00)
    {
        // takes value away from balance
        addBalance(-value);
        std::cout << toString() << std::endl;
        // creates transaction to add to history
        Transaction t("withdraw", value);
        pushHistory(t);
    }
    else
    {
        std::cout << "Balance too low, transaction would exceed overdraft" << std::endl;
    }
}
