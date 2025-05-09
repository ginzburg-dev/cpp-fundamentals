#include <iostream>
#include <string>
#include <string_view>
#include <vector>
#include <utility> // for std::move

template <typename T>
void mySwapCopy(T& a, T& b)
{
    T temp{ a }; // Invokes copy constructor
    a = b; // Invokes copy assignment
    b = temp; // Invokes copy assignment
}

template <typename T>
void mySwapMove(T& a, T& b)
{
    T temp { std::move(a) }; // invokes move constructor
    a = std::move(b); // invokes move assignment
    b = std::move(temp); // invokes move assignment
}

int main()
{
    // Inefficient swap — uses 3 copies instead of moving resources.
    std::string sv1{ "Copy" }; // We use std::string because it is movable (std::string_view is not)
    std::string sv2{ "Swap" };
    mySwapCopy(sv1, sv2);
    std::cout << sv1 << ' ' << sv2 << '\n';

    // Efficient swap using move semantics.
    mySwapCopy(sv1, sv2);
    std::cout << sv1 << ' ' << sv2 << '\n';

    // Vector example
    std::vector<std::string> v;
    std::string str{ "String" };
    v.push_back(str); // calls l-value version of push_back, which copies str into the array element
    std::cout << "Copy semantics of v.push_back. V: " << v[0] << ", Str: " << str << '\n';
    v.push_back(std::move(str)); // calls r-value version of push_back, which moves str into the array element
    std::cout << "Move semantics of v.push_back. V: " << v[1] << ", Str: " << str << '\n';

    str = "New data"; // Moved-from objects are valid but have unspecified values — reset or reassign before reuse.

    return 0;
}
