#include <iostream>

void print(int x, int y = 10)
{
    std::cout << "x, y: " << x << ", " << y << '\n';
}

// If a parameter is given a default argument, 
// all subsequent parameters (to the right) must also be given default arguments.
// Default arguments can not be redeclared, and must be declared before use
// If the function has a forward declaration (especially one in a header file), 
// put the default argument there. Otherwise, put the default argument in the function definition

void printAdd(int x = 10, int y = 10, int z = 20)
{
    std::cout << "x, y, z: " << x << ", " << y << ", " << z << '\n';
}

int rollDie(int sides = 6);
void openLogFile(std::string filename = "default.log");

int main()
{
    print(1);
    print(1,1);
    printAdd();
    printAdd(1,2);
    return 0;
}
