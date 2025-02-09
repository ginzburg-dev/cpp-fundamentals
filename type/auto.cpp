#include <iostream>
#include <string>
#include <string_view>

int add(int a, int b)
{
    return a + b;
}

void foo()
{
}

namespace Goo::Foo
{
    void print()
    {
        std::cout << "Goo" << '\n';
    }
}

// must be fully defined before they can be used.
// typically only callable from within the file in which they are defined
auto af(int a);
auto af(int a)
{
    return a - 1;
}

// when using auto, all return statements within the function must return values of the same type
auto someFcn(bool b)
{
    if (b)
        return 1.0; 
    else
        return 2.5;
}

double divide(int a, int b)
{
    return static_cast<double>(a)/b;
}

auto divide1(int a, int b) -> double
{
    return a/b; 
}

int main()
{
    auto d{ 5.0 };
    auto d1 = 10.3;
    auto sum{ add(10,4) };

    auto a{ 1u };
    auto f{ 4.3f };

    const auto b{ 1.2 };
    constexpr auto c{ 5 };

    //auto error1;
    //auto error2{};
    //auto error3{ foo() };

    const int i{ 1 };
    auto i1{ i }; // i1 has type int (const dropped)

    const auto i2{ i }; // i2 has type int (const dropped but reapplied)

    using Goo::Foo::print;

    print();

    using namespace std::literals;

    auto s1{ "goo"s };
    auto s2{ "moo"sv };

    std::cout << af(1) << '\n';

    std::cout << divide(1, 2) << '\n';
    std::cout << divide1(1, 2) << '\n';

    return 0;
}
