#include <iostream>

class Simple
{
private:
    int m_x{ 0 };

public:
    Simple(int x = 0)
        : m_x { x }
    {
        std::cout << "Constructor\n";
    }

    ~Simple() // here's our destructor
    {
        std::cout << "Destructor\n";
    }
};

int main()
{
    Simple s1 { 1 };

    {
        Simple s2 { 2 };
    }

    return 0;
}
