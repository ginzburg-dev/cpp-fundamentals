#include <iostream>

int getValue()
{
    std::cout << "Enter an integer value: ";
    int x{};
    std::cin >> x;

    return x;
}

int sumTo(int value)
{
    int sum{0};
    for (int x{ 1 }; x <= value; ++x)
        sum += x;
    return sum;
}

void fizzbuzz(int x)
{
    for (int i{ 1 }; i <= x; ++i)
    {
        bool fizz{ i % 3 == 0 };
        bool buzz{ i % 5 == 0 };
        bool pop{ i % 7 == 0 };
        
        if ( fizz )
        {
            std::cout << "fizz";
        }
        if ( buzz )
        {
            std::cout << "buzz";
        }
        if ( pop )
        {
            std::cout << "pop";
        }
        if ( !fizz && !buzz && !pop )
        {
            std::cout << i;
        }

        std::cout << '\n';
    }
}

int main()
{
    //classic for-loop
    for (int i{ 1 }; i <= 10; ++i)
        std::cout << i << ' ';

    std::cout << '\n';

    // an equivalent while-loop
    { // block here to ensure block scope for i
        int i{ 1 };
        while (i <= 10)
        {
            std::cout << i << ' ';
            ++i;
        }

        std::cout << '\n';
    }

    // backwards for-loop
    for (int i{ 10 }; i >= 1; --i)
        std::cout << i << ' ';

    std::cout << '\n';

    // stepped for-loop
    for (int i{ 1 }; i <= 10; i += 2)
        std::cout << i << ' ';

    std::cout << '\n';

    // ommited expressions
    {
        int i{ 1 };
        for ( ; i <= 10; )
        {   
            std::cout << i << ' ';
            ++i;
        }

        std::cout << '\n';
    }

    // for (;;) - infinity loop like while(true)
    for (;;)
    {
        std::cout << "Exit? (Y/N): ";
        char c{};
        std::cin >> c;

        if (c == 'N' || c == 'n') break;
    }

    std::cout << '\n';

    // for-loop with multiple counters
    for (int x{ 1 }, y{ 10 }; x <= 10; ++x, --y)
        std::cout << x << ' ' << y << '\n';
    
    std::cout << '\n';

    // for-loop with char counter
    for (char c{ 'a' }; c <= 'z'; ++c)
        std::cout << c << ' ';
    
    std::cout << '\n';

    // nested for-loop
    for (char c{ 'a' }; c <= 'z'; ++c)
    {
        std::cout << c << ' ';
        for (char x{ 'a' }; x < c; ++x)
            std::cout << x;
        std::cout << '\n';
    }

    // sum of all numbers from 1 to an input value
    {
        int x{ getValue() };
        std::cout << "The sum from 1 to the value is: " << sumTo(x) << '\n';
    }

    // fizzbuzz game. replace numbers divisible by 3 with 'fizz' and numbers divisible by 5 with 'fuzz'
    fizzbuzz( getValue() );

    return 0;
}
