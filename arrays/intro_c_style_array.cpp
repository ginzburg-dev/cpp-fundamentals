#include <iostream>
#include <iterator> // for std::size() and std::ssize()
#include <algorithm> // for std::copy

// get the lengh of an array prior to C++17
template <typename T, std::size_t N>
constexpr std::size_t length( const T(&)[N] ) // T(&)[N] - (&) means reference to array
{
    return N;
}

int main()
{
    int testScores[1];
    constexpr int a[3] {};

    testScores[0] = 1;
    std::cout << testScores[0] << '\n';

    const int arr[] { 1, 2, 3, 4, 5 };
    auto ptr{ arr }; // evaluation causes arr to decay, int*

    int s{1};
    std::cout << arr[s] << '\n'; // C-style array will accept signed or unsigned indexing

    unsigned int u{2}; 
    std::cout << arr[u] << '\n'; // C-style array will accept signed or unsigned indexing

    // auto squares[2] { 1, 4 }; // compile error: can't use type deduction on C-style arrays

    std::cout << sizeof(arr) << '\n'; // size of in bytes
    std::cout << std::size(arr) << '\n'; // the length of the array C++17. <iterator> header
    std::cout << std::ssize(arr) << '\n'; // the length of the array C++20. signed std::ptrdiff_t <iterator> header 
    std::cout << length(arr) << '\n'; // prior to C++17
    std::cout << sizeof(arr) / sizeof(arr[0]) << '\n'; // an old-style alternative length calculation

    //arr = { 5, 4, 3, 2, 1}; // compile error: array assignment not valid.

    int arr1[] { 1, 2, 3, 4, 5 };
    int src[] { 5, 4, 3, 2, 1};
    std::copy(std::begin(src), std::end(src), std::begin(arr1)); // copy src[] to arr1[]


    return 0;
}
