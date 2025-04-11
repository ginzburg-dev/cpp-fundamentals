#include <iostream>
#include <vector>

int fibonacci(std::size_t n)
{
    static std::vector cache{ 0, 1 }; // caching to minimaze function calls

    if ( n < std::size(cache) )
        return cache[n];

    cache.push_back(fibonacci( n - 1 ) + fibonacci( n - 2 ));
    return cache[n];
}

int factorial(int n)
{
    int mult{};

    if ( n <= 0 )
        return 1;
    return n * factorial( n - 1 );
}

int sumDigits(int x)
{
    if (x < 10)
        return x;
    return sumDigits( x / 10 ) + x % 10;
}


int main()
{
    for (int count{0}; count < 13; ++count)
        std::cout << fibonacci(static_cast<std::size_t>(count)) << ' ';
        
    std::cout << '\n';

    for (int count{0}; count < 13; ++count)
        std::cout << factorial(static_cast<std::size_t>(count)) << ' ';

    std::cout << '\n';

    std::cout << sumDigits(93427) << '\n';

    return 0;
}
