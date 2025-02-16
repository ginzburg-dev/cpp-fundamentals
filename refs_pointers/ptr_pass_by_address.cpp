#include <iostream>
#include <string>
#include <cassert>

void printByReference(const std::string& str)
{
    std::cout << str << '\n';
}

void printByAddress(const std::string* ptr)
{
    assert(ptr); // fail the program in debug mode if a null pointer is passed (since this should never happen)

    if (!ptr)
    {
        std::cerr << " printByAddress(const std::string* ptr): Error. ptr is nullptr\n";
        return;
    }

    std::cout << *ptr << '\n';
}

int main()
{
    std::string s { "Hello World!" };
    printByAddress(&s);
    printByReference(s); // Prefer pass by reference to pass by address unless you have a specific reason to use pass by address.

    return 0;
}
