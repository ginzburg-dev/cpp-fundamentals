//#define NDEBUG // to disable asserts in the code
#include <cassert>
#include <iostream>

void printDivision(int x, int y)
{
    assert( y && "Division by zero" );

    if ( y == 0 )
    {
        std::cerr << "Error: Could not divide by zero\n";
        return;
    }

    std::cout << static_cast<double>(x) / y << '\n';
}

int main()
{
    assert(true);
    static_assert(true);

    printDivision(1,0);

    return 0;
}
