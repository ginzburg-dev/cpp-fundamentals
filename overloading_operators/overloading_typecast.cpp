#include <iostream>

// When possible, prefer converting constructors, and avoid overloaded typecasts.
// Typecasts should be marked as explicit, except in cases where the type to be converted to 
// is essentially synonymous with the destination type.

// When you need to define how convert type A to type B:
//If B is a class type you can modify, prefer using a converting constructor to create B from A.
// Otherwise, if A is a class type you can modify, use an overloaded typecast to convert A to B.
// Otherwise use a non-member function to convert A to B.

class Cent
{
private:
    int m_cent{};

public:
    Cent(int cent=0)
        : m_cent{cent}
    {}

    // operator int() const { return m_cent; } // overloaded typecast 
    explicit operator int() const { return m_cent; } // overloaded typecast. 'explicit' keyword does't allow implicit convertions. Only static_cast<int>(Cent)
    int getCent() const { return m_cent; }
    void setCent(int cent) { m_cent = cent; }
};

class Dollar
{
private:
    int m_dollar{};

public:
    Dollar(int dollar=0)
        : m_dollar{dollar}
    {}

    operator Cent() const { return Cent{ m_dollar * 100 }; } // overloaded typecast 
};

void printCent(int cent)
{
    std::cout << "print Cent: " << cent << '\n';
}

void printDollar(Cent cent)
{
    std::cout << "print Dollar: " << static_cast<int>(cent) << '\n'; // Because we have the explicit keyword before the overload, we should use static_cast<int>().
}

int main()
{
    Cent cent{90};
    Dollar dollar{9};

    printCent(static_cast<int>(cent)); // Because we have the explicit keyword before the overload, we should use static_cast<int>().

    printDollar(cent);
    printDollar(dollar); // convertion from dollar to cents - > int

    return 0;
}
