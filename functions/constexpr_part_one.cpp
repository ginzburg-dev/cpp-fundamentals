#include "constexpr_func_multifile.h"
#include <iostream>
#include <type_traits>

int nonConstFunc(int x)
{
    return x;
}

// To make a constexpr function work at both compile-time and runtime 
// while including a non-const function call, use std::is_constant_evaluated()
constexpr auto someFunc(int x) 
{
    if ( std::is_constant_evaluated() )
        return x + 10;
    else
        return nonConstFunc(x);
}

consteval auto compileTimeOnly(int x) // C++ 20: consteval are always evaluated at compile-time
{
    return x * 10;
}

template <typename T, typename U>
constexpr auto mix(T x, U y) // constexpr may be evaluated at either compile-time or runtime
{
    return x * y;
}

int main()
{
    //Always test your constexpr functions in a context that requires a constant expression, 
    //as the constexpr function may work when evaluated at runtime but fail when 
    //evaluated at compile-time.
    constexpr auto mixer{ mix(1, 2.2) }; // args must be constexpr
    std::cout << mixer << '\n';

    double x{ 10.2 };
    int y{ 4 };
    std::cout << mix(x, y) << '\n'; // runtime evaluation

    std::cout << compileTimeOnly(10) << '\n';

    constexpr double multifileConstexprMult{ mult(1.3, 3.3) }; // using constexpr func from header to init
    std::cout << multifileConstexprMult << '\n';

    std::cout << compileTimeOnly(mix<int,int>(10,20))<< '\n'; // in this case constexpr function must be evaluated at compile-time

    constexpr auto compileTimeTest{ someFunc(1) }; // test someFunc() to ensure that it works in compile-time
    std::cout << compileTimeTest << '\n'; // compile time
    std::cout << someFunc(1) << '\n'; // runtime

    return 0;
}
