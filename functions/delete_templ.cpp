#include <iostream>

// will take precedence for arguments of type int
void printInt(int x)
{
    std::cout << x << '\n';
}

template <typename T>
void printInt(T x) = delete; // will takes precedence for args of other types

int main()
{
    printInt(97);
    //printInt(true); // cause halt compilation
    //printInt('a'); // cause halt compilation

    return 0;
}
