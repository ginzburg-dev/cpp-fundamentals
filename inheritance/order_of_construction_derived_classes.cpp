#include <iostream>

// C++ constructs derived classes in phases, starting with the most-base class (at the top of the inheritance tree) 
// and finishing with the most-child class (at the bottom of the inheritance tree). 

class Base
{
public:
    int m_id{};

    Base(int id=0)
        : m_id{id}
    {
        std::cout << "Base\n";
    }

    int getId() const { return m_id; }
};

class Derived : public Base
{
public:
    double m_cost{};

    Derived(double cost=0)
        : m_cost{cost}
    {
        std::cout << "Derived\n";
    }

    double getCost() const { return m_cost; }
};

int main()
{
    std::cout << "Instantiating Base\n";
    Base base;

    std::cout << "Instantiating Derived\n";
    Derived derived;

    /*
    It prints:
    Instantiating Base
    Base
    Instantiating Derived
    Base
    Derived
    */
    return 0;
}
