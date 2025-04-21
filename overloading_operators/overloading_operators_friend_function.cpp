#include <iostream>

class Coin
{
private:
    int m_coin{};

public:
    Coin(int coin)
        : m_coin { coin }
    {}

    int get() const { return m_coin; };

    friend Coin operator+(const Coin& c1, const Coin& c2);
    friend Coin operator+(const Coin& c1, int i);
    friend Coin operator+(int i, const Coin& c1) { return c1 + i; }

    friend Coin operator-(const Coin& c1, const Coin& c2)
    {
        return Coin{ c1.m_coin - c2.m_coin };
    }
};

Coin operator+(const Coin& c1, const Coin& c2)
{
    return Coin{ c1.m_coin + c2.m_coin };
}

Coin operator+(const Coin& c1, int i)
{
    return Coin{ c1.m_coin + i };
}

int main()
{
    Coin c1{ 1 };
    Coin c2{ 2 };

    Coin c3 { c1 + c2 };

    std::cout << c3.get() << '\n';
    
    return 0;
}
