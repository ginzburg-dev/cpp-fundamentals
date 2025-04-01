#include <iostream>
#include <vector>
#include <array>

// Use std::array for constexpr arrays, and std::vector for non-constexpr arrays.

void foo(const int length)
{
    // std::array<int, length> g{}; // compiler error: length is not a constant
}

int main()
{
    std::array<int, 5> a {};

    constexpr int len { 5 };
    std::array<int, len> b{};
    
    enum Color
    {
        red,
        green,
        blue,
        max_colors,
    };

    std::array<int, max_colors> c{};

    const int x{ 10 };
    std::array<int, x> d{};

    std::array<int, 4> arr1 { 1, 2, 3, 4};
    std::array<int, 4> arr2 = { 1, 2, 3, 4 };


    // Define your std::array as constexpr whenever possible. If your std::array is not constexpr, 
    // consider using a std::vector instead.
    constexpr std::array<int, 4> arr3 { 1, 2, 3, 4 };

    constexpr std::array arr4 { 1.3, 3.4, 5.6, 7.8 }; // CTAD C++17

    constexpr std::array word { 'a', 'b', 'c' };
    std::cout << word[1] << '\n';

    constexpr auto arr5 { std::to_array<short>( { 1, 2, 3, 4 } ) }; // if you need to define it without length. Partially ommited.
    return 0;
}
