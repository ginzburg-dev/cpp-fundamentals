#include "class_templates.h"
#include <iostream>
#include <type_traits>
#include <utility> // for std::pair

template <typename T, typename U>
struct Pair
{
    T first{};
    U second{};
};

struct Point
{
    int first{};
    int second{};
};

template <typename T, typename U>
constexpr auto max(Pair<T,U> pair) -> std::common_type_t<T, U>
{
    return ( pair.first > pair.second ) ? pair.first : pair.second;
}

template <typename T, typename U>
void print(Pair<T,U> pair)
{
    std::cout << '[' << pair.first << ", " << pair.second << "]\n";
}

template <typename T>
void print_p(T pair)
{
    std::cout << '[' << pair.first << ", " << pair.second << "]\n";
}

int main()
{
    Pair<int, int> p1{ 5, 6 };
    Pair<int, double> p2{ 6, 3.4 };

    std::cout << max(p2) << '\n';

    print(p1);
    print(p2);

    print_p( Point{ 1, 2 } );

    std::pair p3 { 1, 2.2 };
    print_p(p3);

    Point3d<double> p3d{ 2.0, 3.0, 5.0 };

    std::cout << length(p3d) << '\n';

    return 0;
}
