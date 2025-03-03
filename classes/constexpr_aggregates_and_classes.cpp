#include <iostream>

// If you want your class to be able to be evaluated at compile-time, make your member functions and constructor constexpr.
// constexpr member functions are no longer implicitly const. 
// This means that if you want a constexpr function to be a const function, you must explicitly mark it as such.
class Point
{
private:
    int m_x{};
    int m_y{};

public:
    constexpr Point() = default;
    constexpr Point(const Point& p) = default;
    constexpr Point(int x, int y) : m_x { x }, m_y { y } {}

    constexpr int x() const { return m_x; }
    constexpr int y() const { return m_y; }

    constexpr const int& getX() const { return m_x; } // marks that it can be evaluated at compile time
    constexpr const int* getY() const { return &m_y; } // marks that it can be evaluated at compile time

    constexpr void reset() // constexpr (but non-const) can change an implicit obj memmbers
    {
        m_x = m_y = 0;
    }
};

// Invokes at compile-time even if Point p is non-constexpr since Point class has constexpr constructor and constexpr member function x()
constexpr int Init()
{
    Point p {5, 6};
    return p.x();
}

int main()
{
    constexpr Point p { 5, 6 };
    constexpr int atCompileTime1 { p.x() };
    std::cout << atCompileTime1 << '\n';

    constexpr int atCompileTime2 { Init() };
    std::cout << atCompileTime2 << '\n';

    Point p1 { 5, 6 };
    p1.reset(); // ok
    
    constexpr Point p2 { 5, 6 };
    //p2.reset(); // error: it disallowed, because we are in compile-time now.

    return 0;
}
