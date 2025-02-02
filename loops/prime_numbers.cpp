#include <iostream>

bool isPrime(int x)
{
    if ( x <= 0 )
        return false;

    for (int i{ 2 }; i * i <= x; ++i)
    {
        if (x % i == 0)
            return false;
    }

    return true;
}

int main()
{
    for (int i{1}; i <= 100; ++i)
    {
        assert(isPrime(i));
        if (isPrime(i))
            std::cout << i << '\n';
    }
    return 0;
}
