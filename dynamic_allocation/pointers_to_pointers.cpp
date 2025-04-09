#include <iostream>

int main()
{
    int x{ 10 };
    int* ptr { &x };
    int** ptr1{ &ptr }; 
    std::cout << **ptr1 << '\n'; // Dereference to get an int value of ptr

    int (*array0)[5] { new int[x][5] }; // Pointer to the first array of 5 ints.

    int** array { new int*[10] }; // array of pointers

    for (int i = 0; i < 10; ++i)
        array[i] = new int[5]{}; // This makes two-dimentional array of pointers

    for (int i = 0; i < 10; ++i)
        delete[] array[i];  // deallocated each subarray
    delete[] array; // deallocated main array

    return 0;
}
