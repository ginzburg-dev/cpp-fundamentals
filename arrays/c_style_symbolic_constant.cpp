#include <iostream>
#include <string_view>

int main()
{
    const char a[] { "Hello " }; // 1. put it into a memory somwhere, 2. allocates memory for a C-sytle array
    const char* str { "World!" }; // just put it into a the memory and then initializes a pointer
    
    auto s1{ "Alex" };  // type deduced as const char*
    auto* s2{ "Alex" }; // type deduced as const char*
    auto& s3{ "Alex" }; // type deduced as const char(&)[5]

    std::cout << str << '\n'; // char* always prints as a string

    char c { 'Q' };
    // std::cout << &c << '\n'; // undefined behavior becaude char* prints as string but there is no null terminator

    constexpr std::string_view str1 { "Hello!" }; // prefer this one instead of c-style arrays
    
    return 0;
}
