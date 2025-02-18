#include <iostream>
#include <type_traits>
#include <string_view>

// Stronger Type Safety, No Name Collisions
// No implicit conversion to int (must use static_cast<int>(myColor)).
// Cannot assign int directly (e.g., myColor = 1; is an error).
// Must use Color::Red, so different enums can have the same names without conflicts.

enum class Color
{
    red,
    green,
    blue,
};

template <typename T>
constexpr auto operator+(T a) noexcept
{
    return static_cast<std::underlying_type_t<T>>(a);
}

constexpr std::string_view getColorName(Color color)
{
    using enum Color; // C++20

    switch (color)
    {
    case red: return "red";
    case green: return "green";
    case blue: return "blue";
    default: return "???";
    }
}

int main()
{
    Color color { Color::blue };

    if (color == Color::blue)
        std::cout << "Color is blue.\n";

    std::cout << static_cast<int>(color) << '\n'; // explicit conversion to int, will print 1

    int input{};
    std::cin >> input;

    Color icolor { static_cast<Color>(input) }; // static_cast our integer to a Color
    Color icolor1 { input }; // As of C++17, you can list initialize a scoped enumeration using an integral value without the static_cast

    std::cout << +icolor1 << '\n'; // convert Color to an integer using unary operator+

    std::cout << getColorName(icolor1) << '\n';

    return 0;
}
