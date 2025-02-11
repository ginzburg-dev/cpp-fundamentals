#include <iostream>
#include <string>
#include <type_traits> // for std::common_type_t

template <typename T>
T max(T x, T y)
{
    std::cout << "called max<T>(T, T)\n"; 
    return ( x < y ) ? y : x;
}

int max(int x, int y)
{
    std::cout << "called max(int, int)\n"; 
    return ( x < y ) ? y : x;
}

template <>
double max<double>(double x, double y)
{
    std::cout << "called max<double>(double, double)\n"; 
    return ( x < y ) ? y : x;
}

std::string max(std::string x, std::string y)
{
    std::cout << "called std::string max(std::string x, std::string y)\n"; 
    return ( x.length() < y.length() ) ? y + " " + std::to_string( y.length() ) : x + " " + std::to_string( x.length() );
}

// Use function template specialization to tell the compiler that max(const char*) should emit a compilation error
// const char* will match a string literal
template <>
const char* max(const char* x, const char* y) = delete; 

// using of default arguments for non-template parameters
template <typename T>
void someFnc(T x, int times = 1)
{
    for (int i{times}; i > 0; --i)
    {
        std::cout << x;
    }
}

template <typename T, typename U>
auto maxMulti(T x, U y)
{
    return ( x > y ) ? x : y;
}

// to have a common type of T and U as a return type
template <typename T, typename U>
auto maxMultiCommon(T x, U y) -> std::common_type_t<T, U>
{
    return ( x > y ) ? x : y;
}

// template function override
template <typename T, typename U, typename V>
auto maxMultiCommon(T x, U y, V z) -> std::common_type_t<T, U>
{
    return ( ( ( x > y ) ? x : y ) > z ) ? ( ( x > y ) ? x : y ) : z;
}

// abbreviated function template  from c++20 above. all params are different
auto maxAbbreviated(auto x, auto y)
{
    return ( x > y ) ? x : y;
}

int main()
{
    std::cout << max<int>(1, 2) << '\n';
    std::cout << max<>(1, 2) << '\n';
    std::cout << max<>(1.2, 2.4) << '\n';
    std::cout << max(1, 2) << '\n'; // calls non-template function, favour this call syntax

    std::string hello{ "Hello" };
    std::string world{ "World!" };
    std::cout << max(hello, world) << '\n'; // calls non-template std::string max() function
    //std::cout << max("Hello", "world!") << '\n'; // compile error

    someFnc('a', 3);
    someFnc(5, 1);

    // std::cout << max<>(1.2, 2) << '\n'; // compile error
    std::cout << max<double>(1.2, 2) << '\n'; // correct version. explicitly specify T to convert y to double

    std::cout << maxMulti(1, 2.3) << '\n'; 
    std::cout << maxMultiCommon(2, 2.3) << '\n';
    std::cout << maxMultiCommon(9.32, 2.3, 5.5) << '\n';

    std::cout << maxAbbreviated(1, 5.5) << '\n';

    return 0;
}
