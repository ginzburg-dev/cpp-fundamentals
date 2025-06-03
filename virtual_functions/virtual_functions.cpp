#include <iostream>
#include <string>
#include <string_view>

// A virtual function is a special type of member function that, when called, resolves to the most-derived version 
// of the function for the actual type of the object being referenced or pointed to.
//
// Virtual function resolution only works when a member function is called 
// through a pointer or reference to a class type object.
//
// Never call virtual functions from constructors or destructors.
//
// Compile-time polymorphism refers to forms of polymorphism that are resolved by the compiler. 
// These include function overload resolution, as well as template resolution.
//
// Runtime polymorphism refers to forms of polymorphism that are resolved at runtime. 
// This includes virtual function resolution.

class Animal
{
protected:
    std::string m_name{};

    Animal(std::string_view name)
        : m_name{name}
    {}

public:
    const std::string& getName() const { return m_name; }
    virtual std::string_view speak() const { return "???"; }
};

class Cat : public Animal
{
public:
    Cat(std::string_view name)
        : Animal{name}
    {}

    virtual std::string_view speak() const { return "Meow"; } // If a function is virtual, all matching overrides in derived classes are implicitly virtual.
};

class Dog : public Animal
{
public:
    Dog(std::string_view name)
        : Animal{name}
    {}

    virtual std::string_view speak() const { return "Woof"; }
};

int main()
{
    Cat ginger{"Ginger"};
    Cat ron{"Ron"};
    Cat hazer{"Hazer"};
    Dog joy{"Joy"};

    const Animal* animals[] { &ginger, &ron, &hazer, &joy };
    
    for (const auto* i : animals)
        std::cout << i->getName() << " says " << i->speak() << '\n';

    return 0;
}
