#include <iostream>

// The main reason to use C-style array is first as global constexpr array that can be directly accesable throughout the program for simplicity
constexpr int primes[] = { 2, 3, 5, 7, 11, 13 };

// Another reason is to pass C-style string arg. Because std::string_view requires calculating the length first which can be unnesesary if the func doen't need it
void processCString(const char* str)
{
    while ( *str != '\0' )
    {
        std::cout << *str;
        ++str;
    }
    std::cout << '\n';
}

void printCStyleArrayFirst(const int* arr)
{
    std::cout << arr[0] << '\n';
}

void printElementZero(const int arr[]) // preferable. treated the same as const int*
{
    std::cout << arr[0] << '\n';
}

int main()
{
    const int arr[] { 9, 7, 5, 3, 1 };
    const int* ptr { arr }; // arr decays into a pointer
    std::cout << ptr[2] << '\n'; // subscript[] ptr to get element 2, prints 5
    std::cout << arr[2] << '\n'; // c-style arrays decay to ptr when evalusted. subscript[] gets a value.

    printCStyleArrayFirst(arr);
    
    const char* str { "Hello World!" };
    processCString(str);

    return 0;
}
