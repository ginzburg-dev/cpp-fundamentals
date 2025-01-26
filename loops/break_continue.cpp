#include <iostream>

int main()
{
    std::cout << "Enter an integer from 1 to 3: ";
    int x{};
    std::cin >> x;

    switch(x)
    {
    case 1:
        std::cout << "You've got an option #1\n";
        break; // jump out of switch block
    case 2:
        std::cout << "You've got an option #2\n";
        break; // jump out of switch block
    case 3:
        std::cout << "You've got an option #3\n";
        break; // jump out of switch block
    default:
        std::cout << "Unknown\n";
        break; // jump out of switch block
    }


    for (int i{ 0 }; i <= 100; ++i)
    {
        if ( (i % 7 == 0) || (i % 5 == 0) )
            continue; // skip the loop pass iteration

        std::cout << i << '\n';
        // jump to this point and incriment the counter
    }

    return 0;
}
