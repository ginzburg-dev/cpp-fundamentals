#include <iostream>
#include <typeinfo>

int main()
{
    constexpr int n{ 5 };
    double d{ n };

    int n1{ -5 };
    short s1{ static_cast<short>(n1) };
    //unsigned int u1{ n1 };

    float f1{ 0.1234567 };
    double d1{ f1 };

    constexpr double d2{ 0.1234567 };
    float f2{ d2 };

    constexpr float f3{ 0.1234567 };
    double n2{ f3 };

    std::cout << typeid( 1.0f + 1.0f ).name() << '\n';

    return 0;
}
