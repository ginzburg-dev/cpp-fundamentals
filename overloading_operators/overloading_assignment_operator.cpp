#include <iostream>

class Number
{
private:
    int m_value{};

public:
    // Default constructor
    Number(int number)
        : m_value{number}
    {}
    
    // Copy constructor
    Number(const Number& copy)
        : m_value{copy.m_value}
    {
        std::cout << "Copy constructor called.\n";
    }

    // or use 'delete' keyword to prevent implicit copy assignment
    // Number& operator= (Number& number) = delete;
    // Note that if your class has const members, the compiler will instead define the implicit operator= as deleted. 

    Number& operator= (Number& number) // The copy assignment operator must be overloaded as a member function.
    {
        if ( this != &number ) // working around self-assignment
            m_value = number.m_value;
        
        return *this;
    }

    friend std::ostream& operator<< (std::ostream& out, const Number& number);
};

std::ostream& operator<< (std::ostream& out, const Number& number)
{
    out << number.m_value;
    return out;
}

int main()
{
    Number n1{10};
    Number n2{20};
    Number n3{30};

    Number copy{ n2 };

    n1 = n2 = n3; // chained assignment

    std::cout << n1 << '\n';

    return 0;
}
