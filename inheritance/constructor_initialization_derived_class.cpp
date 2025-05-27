#include <iostream>

class Base
{
private:
    int m_id{};

public:
    Base(int id=0)
        : m_id{id}
    {}

    int getId() const { return m_id; }
};

class Derived : public Base
{
private:
    double m_cost{};

public:
    Derived(int id, double cost)
        : Base{id} // we can use an inherited class constructor to initialize Base class member variables
        , m_cost{cost}
    {}

    double getCost() const { return m_cost; }
};

// Inheritance chains
class A
{
public:
    A(int a)
    {
        std::cout << "A: " << a <<'\n';
    }
};

class B : public A
{
public:
    B(int a, double b)
        : A{a}
    {
        std::cout << "B: " << b <<'\n';
    }
};

class C : public B
{
public:
    C(int a, double b, char c)
        : B{a, b} // constructors can only call constructors from their immediate parent/base class
    {
        std::cout << "C: " << c <<'\n';
    }
}; // When c is destroyed, the C destructor is called first, then the B destructor, then the A destructor.

int main()
{
    Derived derived{ 2, 120.4 };

    std::cout << derived.getId() << '\n';
    std::cout << derived.getCost() << '\n';

    // Inheritance chain
    C c{2, 5.4, 'S'};

    return 0;
}
