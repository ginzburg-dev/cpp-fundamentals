#include <iostream>

int main()
{   
    int selection{};
    do
    {
        std::cout << "Please make a selection: \n";
        std::cout << "1) Addition\n";
        std::cout << "1) Substraction\n";
        std::cout << "1) Multiplication\n";
        std::cout << "1) Division\n";
        std::cin >> selection;
    } while (selection < 1 || selection > 4);

    std::cout << "You selected option #" << selection << '\n';

    return 0;
}
