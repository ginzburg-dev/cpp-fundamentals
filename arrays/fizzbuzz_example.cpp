#include <iostream>
#include <vector>
#include <string>
#include <cassert>

using namespace std::literals;

void buzzFizz(int numbers)
{
    static const std::vector<std::string_view> words {  "fizz"sv , "buzz"sv , "pop"sv , "bang"sv , "jazz"sv , "pow"sv , "boom"sv };
    static const std::vector<int> dividers { 3, 5, 7, 11, 13, 17, 19 };

    assert( std::size(words) == std::size(dividers)  && "fizzbuzz: array sizes don't match" );

    for (int i{ 1 }; i < numbers; ++i)
    {
        bool divisible { false };
        for ( int k{ 0 }; k < dividers.size(); ++k)
        {
            if ( i % dividers[k] == 0 )
            {
                std::cout << words[k];
                divisible = true;
            }
        }
        
        if ( !divisible )
        {
            std::cout << i;
        }
        
        std::cout << '\n';
    }
}

int main()
{
    buzzFizz( 150);

    return 0;
}
