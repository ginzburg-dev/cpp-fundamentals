#include <iostream>


// Favor passing by const reference over passing by non-const reference 
// unless you have a specific reason to do otherwise 
// (e.g. the function needs to change the value of an argument).
// As a rule of thumb, pass fundamental types by value and class types by const reference.
// If you aren’t sure what to do, pass by const reference, as you’re less likely to 
// encounter unexpected behavior.

void printRef(const int& x)
{
    std::cout << x << '\n';
}

void doSomething(const std::string&);
void doSomething(std::string_view);   // prefer this in most cases

// We use a preprocessor function-like macro here so that we can provide either 
// an object OR a type name as a parameter (as C++ functions disallow passing types as a parameter).
// Function-like macro that evaluates to true if the type (or object) is equal to or smaller than
// the size of two memory addresses
#define isSmall(T) { std::cout << #T << " " << ( sizeof(T) <= 2 * sizeof(void*) ) << '\n'; }

struct S
{
    double a;
    double b;
    double c;
};

int main()
{
    std::cout << std::boolalpha;

    int x { 5 };
    printRef(x);

    const int y { 10 };
    printRef(y);

    printRef(5); // 5 is rvalue literal, y binds to temporary int object

    // checking whether types are larger than 2 * sizeof(void*)
    isSmall( std::string{ "Is it small?" } );
    isSmall(int);
    isSmall(S);


    return 0;
}
