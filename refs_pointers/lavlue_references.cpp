#include <iostream>

int g_x { 5 };

int main()
{
    int x{ 10 };
    const int y{ 5 };
    
    // Favor lvalue references to const over lvalue references to non-const 
    //unless you need to modify the object being referenced.
    int& ref{ x };
    const int& constRef{ y };
    const int& constRef1{ x }; // bind a const reference to a modifiable lvalue

    std::cout << x << " " << ref << '\n';
    std::cout << y << " " << constRef << '\n';

    ref = 20;
    std::cout << x << " " << ref << '\n';

    //constRef1 = 10; //error: we can not modify an object through a const reference
    //int& refInit; // error: references must be initialized

    const int& refRval{ 5 }; // surprisingly, lvalues references to const can also bind to rvalues
    std::cout << refRval << '\n';

    const double& r1 { 5 }; // temporary double initialized with value 5, r1 binds to temporary
    std::cout << r1 << '\n'; // prints 5

    char c { 'a' };
    const int& r2 { c }; // temporary int initialized with value 'a', r2 binds to temporary
    std::cout << r2 << '\n'; // prints 97 (since r2 is a reference to int)

    static int s_x { 6 };
    constexpr int& refCexpr{ s_x }; // ok, can bind to static local
    constexpr int& refCexpr1{ g_x }; // ok, can bind to global
    //constexpr int& refCexpr1{ x }; // compile error: can't bind to non-static object

    static const int sc_x { 10 };
    [[maybe_unused]]constexpr const int& refCexprConst { sc_x };

    return 0;
}
