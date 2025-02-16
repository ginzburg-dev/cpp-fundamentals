#include <iostream>

// objects returned by reference must live beyond the scope of the function returning the reference,
// or a dangling reference will result
// Prefer return by reference over return by address unless the ability to return “no object” (using nullptr) is important.

const std::string& returnByReference()
{
    static const std::string s_name { "Passing static string by reference" }; // has static duration, destroyed at the end of proigram

    return s_name;
}

const int& passByReference(const int& x)
{
    return x;
}

const int& max(const int& x, const int& y)
{
    return ( x > y ? x : y );
}

int& maxNonConst(int& x, int& y)
{
    return ( x > y ? x : y );
}

int main()
{
    std::cout << returnByReference() << '\n';

    std::string name { returnByReference() }; // makes a copy
    std::cout << name << '\n'; 

    int x { 10 };
    const int& ref { passByReference(x) };
    x = 20;
    std::cout << x << " " << ref << '\n';

    const int& ref2 { max(1, 2) }; // undefined behavour. dangling ref
    std::cout << ref2 << '\n'; // undefined behavour

    // let's fix that
    int a { 1 };
    int b { 2 };
    const int& ref3 { max(a, b) }; // now it's ok
    std::cout << ref3 << '\n'; // now it's ok
    
    // or this way
    const int value { max(1, 2) }; // ok, copy return value and then it destroyed 
    std::cout << value << '\n'; // now it's ok

    int x1 { 10 };
    int y1 { 20 };
    maxNonConst(x1, y1) = 7; // change max value through returned non-cons ref
    std::cout << x1 << " " << y1 << '\n';

    return 0;
}
