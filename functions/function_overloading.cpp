#include <iostream>

int add(int a, int b)
{
    return a + b;
}

double add(double a, double b)
{
    return a + b;
}

double add(double a, double b, double c)
{
    return a + b + c;
}

int main()
{
    std::cout << add(1, 2) << '\n';
    std::cout << add(1.1, 2.2) << '\n';
    std::cout << add(1.1, 1.2, 1.3) << '\n';

    std::cout << add(static_cast<double>(1), 1.2, 1.3) << '\n'; // explicitly disambiguate the match

    
    return 0;
}
