#include <iostream>

// Overload resolution in derived classes: 
// the compiler will select the best matching function from the most-derived class 
// with at least one function with that name.

class Base
{
private:
    void print() const { std::cout << "private print Base\n"; }

public:
    Base() {}

    friend std::ostream& operator<< (std::ostream& out, const Base&)
    {
        out << "std::cout << const Base&";
        return out;
    }

    void identify() const { std::cout << "Base::identify()\n"; }

    void overridenFunc(int) { std::cout << "Base::overridenFunc(int)\n"; }
    void overridenFunc(double) { std::cout << "Base::overridenFunc(double)\n"; }
};

class Derived : public Base
{
public:
    Derived() {}

    using Base::overridenFunc; // make all Base::overridenFunc() finctions eligible for overload resolution
    void overridenFunc(double) { std::cout << "Derived::overridenFunc(double)\n"; }

    void identify() const 
    { 
        std::cout << "Derived::identify()\n";
        Base::identify(); // call to Base::identify() here
    }

    friend std::ostream& operator<< (std::ostream& out, const Derived& d)
    {
        out << "std::cout << const Derived&\n";
        out << static_cast<const Base&>(d); // static_cast to call the right version of operator<<
        return out;
    }

    void print() const { std::cout << "public print Derived\n"; } // the derived function does not inherit the access specifier of the function with the same name in the base class.
};

int main()
{
    Base base{};
    base.identify();

    Derived derived{};
    derived.identify();
    derived.print();
    
    std::cout << derived << '\n';

    derived.overridenFunc(5);

    return 0;
}
