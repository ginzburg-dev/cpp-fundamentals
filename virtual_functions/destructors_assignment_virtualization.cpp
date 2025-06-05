#include <iostream>
#include <string>
#include <string_view>

// Whenever you are dealing with inheritance, you should make any explicit destructors virtual.
//
// If you intend your class to be inherited from, make sure your destructor is virtual and public.
// If you do not intend your class to be inherited from, mark your class as final. 
// This will prevent other classes from inheriting from it in the first place, 
// without imposing any other use restrictions on the class itself.

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
    std::cout << base->Base::getName() << '\n'; // Prints: Base. Calls Base::getName() instead of the virtualized Derived::getName()

    delete base;

    return 0;
}
