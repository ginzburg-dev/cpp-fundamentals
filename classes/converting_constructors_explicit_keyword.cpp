#include <iostream>
#include <string>

class Employee
{
private:
    std::string m_name{};

public:
    Employee(std::string_view sv)
        : m_name{ sv }
    {}

    const std::string& getName() const { return m_name; }
};

void printEmployee(Employee e)
{
    std::cout << e.getName() << '\n';
}

// An explicit constructor cannot be used to do copy initialization or copy list initialization.
// An explicit constructor cannot be used to do implicit conversions 
// (since this uses copy initialization or copy list initialization).
// Make any constructor that accepts a single argument explicit by default. 
// If an implicit conversion between types is both semantically equivalent and performant, 
// you can consider making the constructor non-explicit.
// Do not make copy or move constructors explicit, as these do not perform conversions.

class Dollar
{
private:
    int m_dollar{};

public:
    explicit Dollar(int dollar) // explicit constructor. 'explicit' keyword only is used only on the declaration
        : m_dollar { dollar }
    {}

    int getDollar() const { return m_dollar; } 
};

void printDollar(Dollar d)
{
    std::cout << '$' << d.getDollar() << '\n';
}

int main()
{
    // printEmployee("Joe"); // error:  only one user-defined conversion may be applied to perform an implicit conversion. this requires two.
    printEmployee( Employee{ "Joe" } );
    //printDollar(5); // error: 'explicit' keyword before the constructor makes it implicitly non-convertible
    printDollar( Dollar{5} ); // ok
    printDollar( static_cast<Dollar>(10) ); // ok
    return 0;
}
