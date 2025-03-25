#include <iostream>
#include <array>

int main()
{
    constexpr std::array<int, 5> arr{ 1, 2, 3, 4, 5 };
    std::cout << arr.size() << '\n'; // .size() returns std::size_t type
    std::cout << std::size(arr) << '\n'; // returns size_type (alias for std::size_t type) 
    std::cout << std::ssize(arr) << '\n'; // returns large signed integral type std::ptrdiff_t

    constexpr int length{ std::size(arr) };

    std::cout << arr.at(1); // runtime bounds checking. try to avoid because we usally do our own bounds checking.
    std::cout << arr[1]; // classic subscript[] operator
    std::cout << std::get<1>(arr); // it's the way you can make compile-time bounds checking. only call with constexpr indices

    std::cout << '\n';

    constexpr std::array arr1{ 'h', 'e', 'l', 'l', 'o' };
    std::cout << arr1[1] << '\n';
    std::cout << arr1.at(1) << '\n';
    std::cout << std::get<1>(arr1) << '\n';
    
    return 0;
}
