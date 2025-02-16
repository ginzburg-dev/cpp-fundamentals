#include <iostream>

// Avoid out-parameters (except in the rare case where no better options exist).
// Prefer pass by reference for non-optional out-parameters.

void multiply(int x, int y, int& out) // we can change an object through int& out param
{
    out = x * y;
}

using Distance = long double;

Distance someFunc(const Distance& in)
{
    Distance dist { in };
    dist += 15.5; // modify it

    return dist;
}

void modifyDist(Distance& inout)
{
    inout += 10;
}

int main()
{
    int x { 5 };
    int y { 2 };
    int result {};

    multiply(x, y, result);

    std::cout << x << " * " << y << " = " << result << '\n';

    // example 1
    Distance distance{ 5 };
    distance = someFunc(distance);

    std::cout << distance << '\n';

    // example 2
    Distance distance1{ 5 };
    modifyDist(distance1);

    std::cout << distance1 << '\n';

    return 0;
}
