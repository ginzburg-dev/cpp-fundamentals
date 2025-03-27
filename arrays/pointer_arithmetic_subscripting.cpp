#include <iostream>

int main()
{
    int x{ 5 };
    const int* ptr{ &x };

    std::cout << ptr << ' ' << ptr + 1 << ' ' << ptr + 2 << '\n'; // It prints: 0x16fdff828 0x16fdff82c 0x16fdff830
    std::cout << ptr << ' ' << ++ptr << ' ' << --ptr << '\n'; // changes the address as well by 4 bytes (the pointer size)

    const int arr[] { 3, 2, 1 };
    
    std::cout << &arr[0] << ' ' << &arr[1] << ' ' << &arr[2] << '\n';
    std::cout << arr[0] << ' ' << arr[1] << ' ' << arr[2] << '\n';
    std::cout << arr << ' ' << (arr + 1) << ' ' << (arr + 2) << '\n'; // ptr math
    std::cout << *arr << ' ' << *(arr + 1) << ' ' << *(arr + 2) << '\n'; // arr decays into const int*. dereferencing and ptr math. arr[n] is equivalent to *((ptr) + (n))

    const int* ptr1{ arr };
    ptr1 = &arr[2];
    std::cout << *ptr1 << ' ' << *(ptr1 + 1) << ' ' << *(ptr1 + 2) << '\n'; // favour pointer math (not subscript) when doing relative positioning from a given element

    // negative indices
    const int* ptr2 { &arr[2] };
    std::cout << *(ptr2 - 1) << ' ' << ptr2[-1] << '\n'; // ptr[-1] == *(ptr - 1)

    // traverse an array
    const int* begin { arr };
    const int* end { arr + std::size(arr)}; 
    for (; begin != end; ++begin)
    {
        std::cout << *begin << ' ';
    }
    std::cout << '\n';

    // range-based for loop 
    for ( auto e : arr )
    {
        std::cout << e << ' ';
    }
    std::cout << '\n';
    
    return 0;
}
