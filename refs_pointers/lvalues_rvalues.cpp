#include <iostream>

// T& is an lvalue reference, so this overload will be preferred for lvalues
template <typename T>
constexpr bool is_lvalue(T&)
{
    return true;
}

// T&& is an rvalue reference, so this overload will be preferred for rvalues
template <typename T>
constexpr bool is_lvalue(T&&)
{
    return false;
}

// #expr converts expr into a string (so it prints the actual expression like "std::string{ "Hello!" }"
#define PRINTVCAT(expr) { std::cout << #expr << " is an " << ( is_lvalue(expr) ? "lvalue\n" : "rvalue\n" ); }

int main()
{
    PRINTVCAT(5); // rvalue
    PRINTVCAT( std::string{ "Hello!" } ); // rvalue
    int x{ 10 };
    PRINTVCAT(x); // lvalue
    PRINTVCAT(++x); // lvalue because ++x increments x first, then it returns a reference to x
    PRINTVCAT(x++); // rvalue because x++ makes a copy of x, then it increments x

    return 0;
}
