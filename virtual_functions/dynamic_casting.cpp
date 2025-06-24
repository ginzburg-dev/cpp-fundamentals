#include <iostream>
#include <string>
#include <string_view>

// Always ensure your dynamic_casts actually succeeded by checking for a null pointer result.
// use static_cast unless you’re downcasting, in which case dynamic_cast is usually a better choice. 
// However, you should also consider avoiding casting altogether and just use virtual functions.
//
// Some compilers allow you to turn RTTI(Run-time type information) off as an optimization. 
// Needless to say, if you do this, dynamic_cast won’t function correctly.


class Base
{
protected:
    int m_value{};

public:
    Base(int value)
        : m_value{value}
    {}

    virtual ~Base() = default;
};

class Derived : public Base
{
protected:
    std::string m_name{};

public:
    Derived(int value, std::string_view name)
        : Base{value}, m_name{name}
    {}

    const std::string& getName() const { return m_name; }
};

Base* getObject(bool returnDerived)
{
    if (returnDerived)
        return new Derived{1, "Derived String"};
    else
        return new Base{2};
}

int main()
{
    // using pointers

    Base* b{ getObject(true) }; // getObject return Derived*
    Derived* d { dynamic_cast<Derived*>(b) }; // downcast to Derived*. If b points to just Base*, return is a null pointer 
    
    if (d)
        std::cout << d->getName() << '\n';

    // using references
    Derived apple{1, "apple"};
    Base& baseRef{ apple };
    Derived& dRef{ dynamic_cast<Derived&>(baseRef) }; // if reference dynamic_cast is falled, it throws an exception std::bad_cast
    
    std::cout << dRef.getName() << '\n';
    

    return 0;
}
