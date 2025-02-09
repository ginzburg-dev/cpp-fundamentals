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

    return 0;
}
