#include <iostream>

int main()
{
    int* ptr = new int;
    int* ptr1 = new int(7);

    int* ptr2{ new int };
    int* ptr3{ new int(7) };
    int* ptr4{ new int{8} };

    int* ptr5{ new (std::nothrow) int }; // It tells compiler not to throw an exception, but instead to return nullptr
    if (!ptr) // handle case where new returned null
    {
        // Do error handling here
        std::cerr << "Could not allocate memory\n";
    }

    std::cout << *ptr4 << '\n';

    delete ptr; // free memory
    ptr = nullptr; // set ptr to nullptr not to have a dangling pointer
    // std::cout << *ptr; // ERROR: dereferensing nullptr

    // We can also do this: If ptr isn't already allocated, allocate it
    if (!ptr)
        ptr = new int;

    // Memory leak
    int value = 10;
    int* ptr6{ new int{2} };
    delete ptr6; // delete before reassigning not to have a memory leak
    ptr6 = &value;

    
    return 0;
}
