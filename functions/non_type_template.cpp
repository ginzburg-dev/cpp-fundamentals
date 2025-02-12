#include <cassert>
#include <iostream>

/*
Non-type template parameters are used primarily 
when we need to pass constexpr values to functions (or class types) 
so they can be used in contexts that require a constant expression.
*/

template <int N>
void print()
{
    static_assert(N > 0, "print(): N must be non-negative");
    std::cout << N << '\n';
}

template <auto N> // deduce non-template parameter from template argument to prevent ambiguous match
void printDeduce()
{
    std::cout << N << '\n';
}

int main()
{
    print<5>();
    // print<-5>(); // compiller error

    printDeduce<1>();
    printDeduce<'a'>();

    return 0;
}
