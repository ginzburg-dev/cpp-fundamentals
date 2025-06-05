#include <iostream>
#include <string>
#include <string_view>

// Whenever you are dealing with inheritance, you should make any explicit destructors virtual.

class Base
{
public:
    virtual ~Base()
    {
        std::cout << "Calling ~Base()\n";
    }

    virtual std::string_view getName() const { return "Base"; }
};

class Derived : public Base
{
private:
    int* m_array{};
public:
    Derived(int length)
        : m_array{ new int[length] }
    {}

    ~Derived() override
    {
        std::cout << "Calling ~Derived()\n";
        delete[] m_array;
    }

    std::string_view getName() const override { return "Derived"; }
};

int main()
{
    Derived* derived{ new Derived(5) };
    Base* base{ derived };
    
    std::cout << base->getName() << '\n'; // Prints: Derived
    std::cout << base->Base::getName() << '\n'; // Prints: Derived

    delete base;

    return 0;
}
