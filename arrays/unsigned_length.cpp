#include <iostream>
#include <vector>

int main()
{
    int s0 { 5 };
    // [[maybe_unused]] unsigned int u0 { s0 }; // error: list initialization disallowed narrowing convention

    constexpr int s { 5 };
    [[maybe_unused]] unsigned int u { s }; // ok: s is constexpr and can be converted safely, not a narrowing conversion

    std::vector v { 1, 2, 3, 4, 5 };
    std::cout << v.size() << '\n';      // size of vector
    std::cout << std::size(v) << '\n';  // size of vector

    int length { static_cast<int>(v.size()) }; // static_cast to prevent narrowing convertion
    std::cout << length << '\n';

    std::cout << std::ssize(v) << '\n'; // std::ssize() returns signed value

    int lengthSsize { static_cast<int>(std::ssize(v)) }; // use static_cast to convert std::ptrdiff_t to int
    auto lengthAuto { std::ssize(v) }; // deduce type

    // subscript operator[] doesn't do bounds checking, but .at() do. slower but safer

    std::vector prime { 2, 3, 5, 7, 11 };
    //std::cout << prime.at(10) << '\n'; // can throw an exception
    std::cout << prime.at(3) << '\n'; // return a reference to array element 3 and print it then

    constexpr int index { 3 };
    std::cout << prime[index] << '\n'; // constexpr int implicitly converted to std::size_t, not a narrowing convertion
    
    int index2 { 1 };
    std::cout << prime[index2] << '\n'; // possible warning: index2 implicitly converted to std::size_t, narrowing convertion

     // Prefer using std::size_t type variable for indexing so not to cluttering your code with convertion things
    std::size_t indexGood1{ 4 };
    std::cout << prime[indexGood1] << '\n'; // operator[] expects an index of type std::size_t, no convertions required

    // Or indexing using data() member function that return pointer to this underlyung C-style array and can allow using both signed a unsigning values to indexing
    int indexGood2 { 1 };
    std::cout << prime.data()[indexGood2] << '\n'; // ok: no sign convertion warnings


    return 0;
}
