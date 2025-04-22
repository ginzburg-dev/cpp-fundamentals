#include <iostream>

// Overloading operators as member functions is preferred when the leftmost operand is *this — for example: '=', '()', '->', '+=', etc.

class Cent
{
private:
    int m_cent{};

public:
    Cent(int cent)
        : m_cent{ cent }
    {}

    int get() const { return m_cent; }

    Cent& operator+=(int value);
    int operator[](int value) const;
    int operator()() const;
    Cent operator+(int value) const;
};

Cent& Cent::operator+=(int value)
{
    this->m_cent += value;

    return *this;
}

int Cent::operator[](int value) const
{
    return value * m_cent;
}

int Cent::operator()() const
{
    return m_cent;
}

Cent Cent::operator+(int value) const
{
    return Cent{ m_cent + value };
}

int main()
{
    Cent c1{ 10 };
    c1 += 6;
    
    std::cout << c1.get() << ' ' << c1() << ' ' << c1[100] << '\n';

    Cent c2{ c1 + 7 };

    std::cout << c2.get() << '\n';

    return 0;
}
