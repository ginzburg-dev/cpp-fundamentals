#include <iostream>

class Simple
{
private:
    int m_value{};

public:
    Simple(int value)
        : m_value{ value }
    {}

    int get() const { return m_value; }

    Simple operator-() const;
    bool operator!() const;
};

Simple Simple::operator-() const
{
    return Simple{ -m_value };
}

bool Simple::operator!() const
{
    return m_value <= 0;
}


int main()
{
    Simple s1{ 10 };

    std::cout << (-s1).get() << '\n';

    Simple s2 { -s1 };

    std::cout << !s2 << '\n';

    return 0;
}
