#include <iostream>
#include <string>
#include <cassert>
#include <cstddef> // dor std::nullptr_t

void print(std::nullptr_t)
{
    std::cout << "in print(std::nullptr_t)\n";
}
void print(int*)
{
    std::cout << "in print(int*)\n";
}

void add(int* ptr2)
{
    ++*ptr2;
}

void nullify(int*& refptr)
{
    refptr = nullptr;
}

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

    int x { 1 };
    add(&x);
    std::cout << x << '\n';

    int* ptr { &x };
    std::cout << "ptr is " << (ptr ? "non-null\n" : "null\n");
    nullify(ptr);
    std::cout << "ptr is " << (ptr ? "non-null\n" : "null\n");

    print(nullptr); // calls print(std::nullptr_t)
    ptr = nullptr;
    print(ptr); // calls print(int*) since ptr has type int*

    return 0;
}
