#include <iostream>
#include <optional>

/*
Prefer std::optional for optional return types.
Prefer function overloading for optional function parameters (when possible). 
Otherwise, use std::optional<T> for optional arguments when T would normally be passed by value. 
Favor const T* when T is expensive to copy.
*/

void printNumber(std::optional<int> x = std::nullopt) // It effectively documents, we can pass in an rvalue (since std::optional will make a copy)
{
    if (x)
        std::cout << "The number is " << *x << '\n';
    else
        std::cout << "The number is unknown\n";
} 

void printNumberPtr(const int* x = nullptr) // the pointer version
{
    if (x)
        std::cout << "The number is " << *x << '\n';
    else
        std::cout << "The number is unknown\n";
}

void printOverload()
{
    std::cout << "() The number is unknown\n";
}

void printOverload(const int& x)
{
    std::cout << "(const int&) The number is " << x << '\n';
}

std::optional<int> divide(int x, int y)
{
    if ( y == 0 )
        return std::nullopt; // or return {};
    return x / y;
}

int main()
{
    std::optional<int> result1 { divide(20, 5) };
    if (result1)
        std::cout << *result1 << '\n';
    else
        std::cout << "Result1: failed\n";
    
    std::optional<int> result2 { divide(20, 0) };
    if (result2)
        std::cout << *result2 << '\n';
    else
        std::cout << "Result2: failed\n";



    std::optional<int> o1 { 5 };            // initialize with a value
    std::optional<int> o2 {};               // initialize with no value
    std::optional<int> o3 { std::nullopt }; // initialize with no value

    if (o1.has_value()) // call has_value() to check if o1 has a value
    if (o2)             // use implicit conversion to bool to check if o2 has a value

    o1 = 10;
    o2 = 20;

    std::cout << *o1;             // dereference to get value stored in o1 (undefined behavior if o1 does not have a value)
    std::cout << o2.value();      // call value() to get value stored in o2 (throws std::bad_optional_access exception if o2 does not have a value)
    std::cout << o3.value_or(42); // call value_or() to get value stored in o3 (or value `42` if o3 doesn't have a value)

    printNumber();
    printNumber(100);

    int x{ 5 };
    printNumberPtr(&x);

    printOverload();
    printOverload(x);

    return 0;
}
