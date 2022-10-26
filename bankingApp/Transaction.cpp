#include "Transaction.h"
#include <iostream>
#include <string>
#include <chrono>

/// <summary>
/// constructor to set attributes
/// </summary>
/// <param name="_desc">		description of transaction		</param>
/// <param name="_value">		value of transaction		</param>
Transaction::Transaction(std::string _desc, double _value)
{
    desc = _desc;
    value = _value;
    // Gets a time_point of the current date and time
    timestamp = std::chrono::system_clock::now();
}

// Transaction::~Transaction() { std::cout << "Transaction destroyed" << std::endl; }
Transaction::~Transaction() {} // destructor

/// <summary>
/// creates output message for transactions
/// </summary>
/// <returns></returns>
std::string Transaction::toString()
{
    // Converts time_point to time_t
    time_t t = std::chrono::system_clock::to_time_t(timestamp);
    // Will put t into the array of characters str
    char str[26];
    ctime_s(str, sizeof str, &t);

    std::string out = "-- " + desc + ": \x9C" + std::to_string(value) + " " + str;
    return out;
}

double Transaction::getValue() { return value; } // gets value
