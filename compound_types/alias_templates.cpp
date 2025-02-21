#include <iostream>

template <typename T>
struct Pair
{
    T first{};
    T second{};
};

template <typename T>
Pair(T, T) -> Pair<T>;

// alias templates must be defined in the global scope (as all templates must)
template <typename T>
using Coord = Pair<T>;

// CTAD doesn’t work on function parameters
template <typename T>
void print(const Coord<T>& coord)
{
    std::cout << '[' << coord.first << ", " << coord.second << "]\n";
}

int main()
{
    Coord<int> c1 { 1, 2 };
    //Coord c2 { 3.0, 4.0 };  // clang++ 16!! In C++20, Coord p2 {1, 2}; works if Pair has a deduction guide.

    return 0;
}
