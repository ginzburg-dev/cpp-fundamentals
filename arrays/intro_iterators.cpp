#include <iostream>
#include <array> // includes <iterator>

int main()
{
    std::array array { 1, 2, 3, 4, 5 };
    auto begin { &array[0] };
    auto end { begin + std::size(array) };

    for (auto ptr {begin}; ptr != end; ++ptr )
        std::cout << *ptr << ' ';
    std::cout << '\n';

    std::array arr { 6, 12, 5, 23, 7 };
    auto begin_arr { std::begin(arr) };
    auto end_arr { std::end(arr) };

    for (auto ptr{begin_arr}; ptr != end_arr; ++ptr)
        std::cout << *ptr << ' ';
    std::cout << '\n';

    return 0;
}
