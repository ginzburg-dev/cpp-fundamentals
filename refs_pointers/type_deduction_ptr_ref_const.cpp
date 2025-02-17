#include <iostream>
#include <string>
#include <string_view>

std::string& getRef(std::string& str) // some function that returns a reference
{
    return str;
}

const int& someFunc(const int& x)
{
    return x;
}

constexpr std::string_view hello { "Hello" }; // implicitly const

constexpr const std::string_view& getConstRef(const std::string_view& str)
{
    return str;
}

int* getPtr(int* ptr)
{
    return ptr;
}

int main()
{
    std::string str { "Just string" };
    auto ref1 { getRef(str) }; // type deduced as std::string
    auto& ref2 { getRef(str) }; // type deduced as std::string& (reference dropped, reference reapplied)

    int x { 5 };                        
    auto ref3 { someFunc(x) };        // std::string (reference and top-level const dropped)
    const auto ref4 { someFunc(x) };  // const std::string (reference dropped, const dropped, const reapplied)
    auto& ref5 { someFunc(x) };       // const std::string& (reference dropped and reapplied, low-level const not dropped)
    const auto& ref6 { someFunc(x) }; // const std::string& (reference dropped and reapplied, low-level const not dropped)

    auto ref7 { getConstRef(hello) };                   // std::string_view (reference dropped and top-level const dropped)
    constexpr auto ref8 { getConstRef(hello) };         // constexpr const std::string_view (reference dropped and top-level const dropped, constexpr applied, implicitly const)
    auto& ref9 { getConstRef(hello) };                  // const std::string_view& (reference reapplied, low-level const not dropped)
    constexpr const auto& ref10 { getConstRef(hello) }; // constexpr const std::string_view& (reference reapplied, low-level const not dropped, constexpr applied)

    auto ptr1 { getPtr(&x) }; // int*
    auto* ptr2 { getPtr(&x) }; // int* (initializer must be a pointer)

    const auto ptr3 { getPtr(&x) }; // int* const
    auto const ptr4 { getPtr(&x) }; // int* const

    const auto* { getPtr(&x) }; // const int*
    auto* const { getPtr(&x) }; // int* const

    std::string s {};
    const std::string* const ptr_s { &s };

    auto ptr_s1 { ptr_s }; // const std::string*
    auto* ptr_s2 { ptr_s }; // const std::string*

    auto const ptr_s3 { ptr_s }; // const std::string* const
    const auto ptr_s4 { ptr_s }; // const std::string* const

    auto* const ptr_s5 { ptr_s }; // const std::string* const
    const auto* ptr_s6 { ptr_s }; // const std::string*

    // const auto const ptr_s7 { ptr_s }; // error: const qualifer can not be applied twice
    const auto* const ptr_s7 { ptr_s }; // const std::string* const

    return 0;
}
