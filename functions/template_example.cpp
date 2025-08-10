//#define NDEBUG
#include <cassert>
#include <iostream>

template <typename T>
auto add(T x, T y)
{
    return x + y;
}

template <typename T>
T mult(T x, int y)
{
    return x * y;
}

template <typename T, typename U>
auto divide(T x, U y) -> double
{
    assert(y);
    if ( y == 0 )
    {
        std::cerr << "error: division by zero\n";
        return 0.0;
    }

    return static_cast<double>(x) / y;
}

int main()
{
    std::cout << add(1, 2) << '\n';
    std::cout << add(1.1, 2.2) << '\n';

    std::cout << mult(2, 3) << '\n';
    std::cout << mult(1.2, 3) << '\n';

    std::cout << divide(1, 2) << '\n';
    std::cout << divide(1, 0) << '\n';
    
    return 0;
}
