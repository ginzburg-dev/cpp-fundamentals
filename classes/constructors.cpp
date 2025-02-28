#include <iostream>
#include <optional>

class Point
{
private:
    double m_x{};
    double m_y{};
public:
    // Member variables in a member initializer list should be listed in order that they are defined in the class.
    Point(double x, double y) // constructor (preferred)
        : m_x { x }
        , m_y { y }
    {
        std::cout << "Point(" << x << ", " << y << ") constructed\n";
    }

    Point(double d) : m_x { d }, m_y { d } {} // constructor

    void print() const
    {
        std::cout << "Point(" << m_x << ", " << m_y << ")\n";
    }
};

// another way to handle with violating class invarianriants
class Fraction
{
private:
    int m_numerator{};
    int m_denominator{}; // invariant: must be non zero

    Fraction(int numerator, int denominator) // private constructor to prevent construct class using member-initializer-list
        : m_numerator { numerator }
        , m_denominator { denominator }
    {
    }

public:
    friend std::optional<Fraction> createFraction(int numerator, int denominator);
};

std::optional<Fraction> createFraction(int numerator, int denominator)
{
    if ( denominator == 0 )
        return {}; // or throw std::nullopt as a return

    return Fraction{ numerator, denominator };
}

int main()
{

    Point p{ 2.3, 4.5 };
    p.print();

    Point p1{ 6.7 };
    p1.print();

    std::optional<Fraction> f1 { createFraction( 1, 0 ) }; // or auto f1 { createFraction( 1, 0 ) };
    if ( !f1 )
    {
        std::cerr << "Bad fraction\n";
    } 
    else
    {
        std::cout << "Fraction created\n";
    }

    return 0;
}
