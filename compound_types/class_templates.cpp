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

// Here's a deduction guide for our Pair (needed in C++17 only). now you can initioalize like Pair p4 {1, 2}; as well as Pair<T,U> p4 {1, 2};
template <typename T, typename U>
Pair(T, U) -> Pair<T, U>;

struct Point
{
    int first{};
    int second{};
};

template <typename T>
struct Point2d
{
    T x{};
    T y{};
};

// a deduction guide
template <typename T>
Point2d(T, T) -> Point2d<T>;

template <typename T=int, typename U=int> // default T and U to type int
struct DefaultIntStruct
{
    T one{};
    U two{};
};

struct Foo
{
    // CTAD doesn’t work with non-static member initialization
    // DefaultIntStruct p1 { 1, 2 }; // error
    DefaultIntStruct<int, int> p1 { 1, 2 }; //  initializing the member of a class type. All template arguments must be explicitly specified
};

template <typename T, typename U>
DefaultIntStruct(T, U) -> DefaultIntStruct<T, U>;

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

// void print_p1(std::pair p) // compile error, CTAD can't be used here
// In such cases, you should use a template instead:
template <typename T, typename U>
void print_p1(std::pair<T, U> p)
{
    std::cout << p.first << ' ' << p.second << '\n';
}

int main()
{
    Pair<int, int> p1{ 5, 6 };
    Pair<int, double> p2{ 6, 3.4 };
    Pair p4 {1, 2};

    std::cout << max(p2) << '\n';

    print(p1);
    print(p2);

    print_p( Point{ 1, 2 } );

    std::pair p3 { 1, 2.2 };
    print_p(p3);

    Point2d p2d { 2.2, 3.3 };

    Point3d<double> p3d{ 2.0, 3.0, 5.0 };
    Point3d p3d1{ 2.0, 3.0, 5.0 };

    std::cout << length(p3d) << '\n';

    

    return 0;
}
