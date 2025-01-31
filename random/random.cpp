#include "random.h"
#include <iostream>

int main()
{
    std::cout << Random::get(1,6) << '\n'; // return int between 1 and 6
    std::cout << Random::get(1l,6u) << '\n'; // different types of arguments

    std::cout << Random::get<std::size_t>(1,6u) << '\n'; // return std::size_t between 1 and 6 

    // reusable generator 
    std::uniform_int_distribution<> die6{1, 6};
    for (int i{ 1 }; i <= 10; ++i)
    {
        std::cout << die6(Random::mt) << ' ';
    }

    std::cout << '\n';
    
    return 0;
}
