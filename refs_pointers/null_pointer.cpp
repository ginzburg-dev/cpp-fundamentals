#include <iostream>

/*
Whenever you are using pointers, you’ll need to be extra careful that your code isn’t dereferencing null 
or dangling pointers, as this will cause undefined behavior (probably an application crash).
*/

void someFunction(int* x)
{   
    if ( x == nullptr )
    {
        std::cerr <<  "Error in someFunction(int* x): x is nullpointer\n";
        return;
    }

    std::cout << *x << '\n';
}

int main()
{
    int* ptr {}; // null pointer
    int* ptr1 { nullptr }; // null pointer

    int x { 5 };
    int* ptr2 { &x };
    ptr2 = nullptr; // can assign nullptr to make the pointer a null pointer

    someFunction(nullptr); // we can also pass nullptr to a function that has a pointer parameter

    // is ptr null
    if (ptr) // implicit conversion to Boolean
        std::cout << "ptr is non-null\n";
    else
        std::cout << "ptr is null\n";

    std::cout << "ptr is " << ( ptr ? "non-null\n" : "null\n" ); // implicit conversion to Boolean

    return 0;
}
