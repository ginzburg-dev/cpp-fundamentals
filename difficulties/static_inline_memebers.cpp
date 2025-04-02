#include <iostream>
#include <array>

// inline is used mostly with static vae in a header to avoid multiple difinition across different translation units
// in C++17 and later, constexpr variables are implicitly inline if they are defined inside a class or in a header file.
class X
{
public:
    static const int i = 10; // works because integral and enumeration static constants inside a class are treated as compile-time constants and don’t require an out-of-class definition
    static std::array<int, 3> arr; // just declaration, no storage neded
    static std::array<int, 3> arr2; 
    // constexpr std::array<int, 3> arr1; // ERROR: because it's going to be instantiated and you are not allowed to have multiple constexpr memory allocation, just once
    static inline std::array<int, 3> arr3 { 2, 3, 4 }; // like out decl with inline so that it can be used in differrent translation units without odr violation. constexpr makes it implicitly inline as well
    static constexpr std::array<int, 3> arr4 { 2, 3, 4 }; // Or this
};

std::array<int, 3> X::arr { 1, 2, 3 }; // if it added to multiple files, it would neeed an inline keyword (ODR)
inline std::array<int, 3> X::arr2 { 1, 2, 3 }; // an example of out definition if it would be placed in multiple files ( if defined inside a header for example)

int main()
{
    return 0;
}
