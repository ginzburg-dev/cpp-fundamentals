#include <iostream>

// There may be times when we have access to a base class but do not want to modify it. 
// Consider the case where you have just purchased a library of code from a 3rd party vendor, 
// but need some extra functionality. You could add to the original code, but this isn’t the best solution. 
// What if the vendor sends you an update? Either your additions will be overwritten, 
// or you’ll have to manually migrate them into the update, which is time-consuming and risky.
//
// In either case, the best answer is to derive your own class, 
// and add the functionality you want to the derived class.

class Base
{
protected: // can be accessed by Derived classes
    int m_value{};

public:
    Base(int value)
        : m_value{value}
    {}

    void identify() const { std::cout << "I'm a Base class\n"; }
};

class Derived : public Base
{
public:
    Derived(int value)
        : Base{value}
    {}

    int getValue() const { return m_value; } // add new functionality to a Derived class to get m_value from the Base class
};

int main()
{
    Derived derived{ 5 };
    std::cout << "derived has value " << derived.getValue() << '\n';

    return 0;
}
