#include <iostream>

/*
L-value reference:
    - Can be initialized with: 
        Modifiable l-values
    - Can modify: 
        Modifiable l-values

L-value reference to const:
    - Can be initialized with: 
        Modifiable l-values
        Non-modifiable l-values
        R-values
    - Can't modify any bound objects


R-value reference:
    - Can be initialized with: 
        R-values
    - Can modify: 
        R-values

R-value reference to const:
    - Can be initialized with: 
        R-values
    - Can't modify any bound objects

l-ref : int& lref{};
r-ref:  int&& rref{};

Important:
    You should almost never return an r-value reference, for the same reason 
    you should almost never return an l-value reference. In most cases, 
    you’ll end up returning a hanging reference when 
    the referenced object goes out of scope at the end of the function.

*/

class Fraction
{
private:
	int m_numerator { 0 };
	int m_denominator { 1 };

public:
	Fraction(int numerator = 0, int denominator = 1) :
		m_numerator{ numerator }, m_denominator{ denominator }
	{
	}

	friend std::ostream& operator<<(std::ostream& out, const Fraction& f1)
	{
		out << f1.m_numerator << '/' << f1.m_denominator;
		return out;
	}
};

void func(const int& lref)
{
    std::cout << "l-value reference to const: " << lref << '\n';
}

void func(int&& rref)
{
    std::cout << "r-value reference: " << rref << '\n';
}

int main()
{
    auto&& rref{ Fraction{ 2, 4 } }; // r-reference extends the lifespan of the temporary object it is bbound to
    std::cout << rref << '\n';
    
    int&& rref1 { 5 }; // because we're initializing an r-value reference with a literal, a temporary with value 5 is created here
    rref1 = 10; // It's possible to modify this temporary object as well.
    std::cout << rref1 << '\n';

    int x{ 5 };
    func(x); // l-value argument calls l-value version of function
    func(5); // r-value argument calls r-value version of function
    func(rref1); // l-value version of function! int&& rref1 : rref1 is an l-value of type int&& so that l-value argument calls l-value version of function

    return 0;
}
