#include <algorithm>
#include <cmath>
#include <cstddef>
#include <iostream>
#include <limits>
#include <vector>
#include "../random/random.h"

using Numbers = std::vector<int>;

namespace Config
{
    constexpr int multiplierMin{ 2 };
    constexpr int multiplierMax{ 4 };
}

int getNumber()
{
    while (true)
    {
        int number{};
        std::cin >> number;

        if( !std::cin )
        {
            std::cin.clear();
            std::cin.ignore( std::numeric_limits<std::streamsize>::max(),'\n');
            std::cout << "It's a wrong input. Try again: ";
            continue;
        }

        std::cin.ignore( std::numeric_limits<std::streamsize>::max(),'\n');

        return number;
    }
}

Numbers generateNumbers(int start, int length, int multiplier)
{
    Numbers numbers(static_cast<std::size_t>(length));

    int nextNumber{start};
    for ( auto& i : numbers )
    {
        i = multiplier * nextNumber * nextNumber;
        nextNumber++;
    }

    std::cout << "I generated " << length 
    << " guess numbers. Do you know what each number is after multiplying it by " 
    << multiplier << "?\n";

    return numbers;
}

Numbers setupGame()
{
    std::cout << "Start where? ";
    int start{ getNumber() };

    std::cout << "How many? ";
    int length{ getNumber() };

    return generateNumbers(start, length, Random::get(Config::multiplierMin, Config::multiplierMax));
}

int getUserGuess()
{
    std::cout << ">";

    return getNumber();
}

bool findAndRemove(Numbers& numbers, int guess)
{
    auto found { 
        std::find(numbers.begin(), numbers.end(), guess)
    };

    if ( found == numbers.end() )
        return false;

    numbers.erase(found);
    return true;
}

int findClosestNumber(const Numbers& numbers, int guess)
{
    return *std::min_element(numbers.begin(), numbers.end(), 
        [=](const int& a, const int& b)
        { 
            return std::abs( guess - a ) < std::abs( guess - b );
        } );
}

void printSuccess(const Numbers& numbers)
{
    std::cout << "Nice! ";

    if ( numbers.size() == 0 )
    {
        std::cout << "You found all numbers, good job!\n";
    }
    else
    {
        std::cout << numbers.size() << " number(s) left.\n";
    }
}

void printFalure(const Numbers& numbers, int guess)
{
    int closest{ findClosestNumber(numbers, guess) };
    std::cout << guess << " is wrong! ";
    std::cout << "Try " << closest << " next time.\n";
}

int main()
{
    Numbers numbers { setupGame() };

    while(true)
    {
        int guess{ getUserGuess() };

        if ( !findAndRemove(numbers, guess) )
        {
            printFalure(numbers, guess);
            break;
        }

        printSuccess(numbers);
        if ( numbers.size() == 0 )
            break;
    }

    return 0;
}
