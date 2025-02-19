#include <iostream>

struct Fraction
{
    int numerator {};
    int denominator {};
};

Fraction inputFraction()
{
    std::cout << "Enter a value for the numerator: ";
    Fraction fraction{};
    std::cin >> fraction.numerator;
    std::cout << "Enter a value for the denominator: ";
    std::cin >> fraction.denominator;
    std::cout << '\n';

    return fraction;
}

constexpr Fraction mult(const Fraction& f1, const Fraction& f2)
{
    return Fraction{ .numerator = f1.numerator * f2.numerator, .denominator = f1.denominator * f2.denominator };
}

std::ostream& operator<<(std::ostream& out, const Fraction& fraction)
{
    out << fraction.numerator << '/' << fraction.denominator;
    return out;
}

int main()
{
    Fraction f1 { inputFraction() };
    Fraction f2 { inputFraction() };

    std::cout << "Your fractions multiplied together: " << mult(f1,f2) << '\n';
    
    return 0;
}
