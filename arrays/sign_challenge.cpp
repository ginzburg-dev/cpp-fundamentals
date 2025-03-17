#include <iostream>
#include <vector>

// Avoid array indexing with integral values whenever possible.

using Index = std::ptrdiff_t; // signed counterpart to std::size_t

int main()
{
    std::vector arr { 1, 2, 3, 4, 5 };

    auto length { static_cast<Index>(arr.size()) };
    for ( auto index { length - 1 }; index >=0; --index )
        std::cout << arr[static_cast<std::size_t>(index)] << ' ';

    for ( auto index { std::ssize(arr) - 1 }; index >=0; --index) // std::ssize returns signed value from C++20 onwards.
        std::cout << arr[static_cast<std::size_t>(index)] << ' ';

    for ( auto index { std::ssize(arr) - 1 }; index >=0; --index) // std::ssize returns signed value from C++20 onwards.
        std::cout << arr.data()[index)] << ' '; // use data() to avoid sign conversion warning
    
    return 0;
}
