#pragma once
#include <string>
#include <chrono>

class Transaction
{
private:
    std::string desc;
    double value;
    std::chrono::system_clock::time_point timestamp; // stores a point in time

public:
    Transaction(std::string _desc, double _value);
    ~Transaction();
    std::string toString();
    double getValue();
};