#include <iostream>
#include <string>

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

    return 0;
}
