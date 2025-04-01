#include <iostream>
#include <cassert>
#include <array>

template <typename T, std::size_t N>
void passByRef(const std::array<T, N>& arr)
{
    static_assert( N != 0 );

    std::cout << arr[0] << '\n';
}

template <typename T, std::size_t N>
std::array<T, N> returnArrayByValue(const std::array<T, N>& arr)
{
    return arr; // return by value
}

template <typename T, std::size_t N>
void modifyArray(std::array<T, N>& arr) // pass by non - const ref to modify it
{
    arr[0] = 1;
}

template <typename T, std::size_t N>
void printArray(const std::array<T, N>& arr)
{
    std::cout << "The array ( ";
    for ( const auto& i : arr )
    {
        std::cout << i << ' ';
    }
    std::cout << ") has length " << std::size(arr) << '\n';
}

int main()
{
    constexpr std::array arr { 1, 2, 3 };
    passByRef(arr);
    

    constexpr std::array arr1 { 'h', 'e', 'l', 'l', 'o' };
    printArray(arr1);

    return 0;
}
