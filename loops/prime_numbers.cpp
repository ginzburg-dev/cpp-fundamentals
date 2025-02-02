#include <iostream>

// retrn true value if given number is prime
bool isPrime(int x)
{
    if ( x <= 0 )
        return false;

    // loop from 2 to square root of current number std::sqrt(x) 
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
        if (isPrime(i))
            std::cout << i << '\n';
    }

    return 0;
}
