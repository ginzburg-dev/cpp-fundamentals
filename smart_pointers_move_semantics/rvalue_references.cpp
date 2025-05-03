#include <iostream>

/*
L-value reference:
    - Can be initialized with: 
        Modifiable l-values
    - Can modify: 
        Modifiable l-values

R-value reference to const:
    - Can be initialized with: 
        Modifiable l-values
        Non-modifiable l-values
        R-values
    - Can't modify any bound objects

l-ref : int& lref{};
r-ref:  int&& rref{};
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
    func(rref1); 
    return 0;
}
