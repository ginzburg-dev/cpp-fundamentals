#include <cstdint>
#include <iostream>
#include <string>

int getValue(std::string_view name)
{
    std::cout << "Enter an integer " << name << " value: ";
    int x;
    std::cin >> x;

    return x;
}

std::int64_t pow(int base, int exponent)
{
    std::int64_t total{ 1 };
    for (int i{ 0 }; i < exponent; ++i)
        total *= base;
    
    return total;
}

int main()
{
    int base{ getValue("base") };
    int exponent{ getValue("exponent") };

    std::cout << pow(base, exponent) << '\n';

    return 0;
}

