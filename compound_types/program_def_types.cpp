#include "Fraction2.h"
#include <iostream>

struct Fraction
{
    int numerator{};
    int denominator{};
}; // don’t forget to end your type definitions with a semicolon.

int main()
{
    Fraction f {1, 5};
    Fraction2 f2 {2, 5};
    
    return 0;
}
