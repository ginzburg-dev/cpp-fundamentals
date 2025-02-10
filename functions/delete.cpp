#include <iostream>

void printInt(int x)
{
    std::cout << x << '\n';
}

void printInt(char) = delete; // halt compilation
void printInt(bool) = delete; // halt compilation

int main()
{
    printInt(97);
    //printInt(true); // cause halt compilation
    //printInt('a'); // cause halt compilation

    return 0;
}
