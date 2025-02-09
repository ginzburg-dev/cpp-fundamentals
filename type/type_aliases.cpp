#include "type_aliases_h.h"
#include <iostream>


using Distance = long double;
typedef double Height; // prefer not to use it, unless for backwards capability

constexpr Distance getDistance(double a, double b)
{
    return std::abs( a - b );
}

int main()
{
    Distance distance{ getDistance(5, 19) };
    std::cout << distance << '\n';

    // Weight from type_aliases_h.h
    Weight weight{ 3.2 };
    std::cout << weight << '\n';

    return 0;
}
