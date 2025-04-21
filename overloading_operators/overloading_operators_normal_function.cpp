#include <iostream>
// Prefer overloading operators as normal functions 
// instead of friends if it’s possible to do so without adding additional functions.

// Cents.h
#ifndef CENTS_H
#define CENTS_H

class Cents
{
private:
    int m_cents{};

public:
    Cents(int cents)
        : m_cents{ cents }
    {}

    int getCents() const { return m_cents; }
};

#endif

// Cents.cpp
Cents operator+(const Cents& c1, const Cents& c2)
{
    return Cents{ c1.getCents() + c2.getCents() };
}

// main.cpp
int main()
{

    Cents c1 { 6 };
    Cents c2 { 8 };

    Cents centsSum{ c1 + c2 };

    std::cout << "I have " << centsSum.getCents() << " cents.\n";

    return 0;
}
