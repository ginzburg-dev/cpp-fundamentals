#include <iostream>

namespace ProgramData
{
    constexpr int perfectSquares[] { 0, 1, 4, 9 };
}

bool matchSquare( int number )
{
    for ( const int& i : ProgramData::perfectSquares )
    {
        if ( i == number )
            return true;
    }

    return false;
}

int main()
{
    while(true)
    {
        std::cout << "Enter a single digit integer, or -1 to quit: ";
        int input{};
        std::cin >> input;

        if (input == -1)
        {
            std::cout << "Bye\n";
        }
        
        if(matchSquare(input))
            std::cout << input << " is a perfect square\n";
        else
            std::cout << input << " is not a perfect square\n";
    }

    return 0;
}
