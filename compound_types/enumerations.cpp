#include <iostream>
#include <optional>
#include <string>
#include <string_view>

enum Color
{
    red, // So red is put into the global namespace
    green,
    blue, // Trailing comma optional but recommended
}; // The enum definition must end with a semicolon

// Use namespaces to prevent neme collisions 
namespace State
{
    enum State
    {
        idle, // “unknown” enumerator with value 0
        walk,
        run,
        jump,
    };
    
}

enum Animals
{
    cat = -3,    // -3
    dog,         // -2
    pig,         // -1
    horse = 5,   // 5
    giraffe = 5, // 5
    chicken,     // 6
};

enum Pets
{
    parrot,
    fox,
    cow,
};

// Use an 8-bit integer as the enum underlying type
enum Spec : std::int8_t
{
    spec1,
    spec2,
};

constexpr std::string_view getPetName(Pets pet)
{
    switch (pet)
    {
    case parrot: return "parrot";
    case fox: return "fox";
    case cow: return "cow";
    default: return "???";
    }
}

constexpr std::optional<Pets> getPetFromString(std::string_view sv)
{
    if (sv == "parrot") return Pets::parrot;
    if (sv == "fox") return Pets::fox;
    if (sv == "cow") return Pets::cow;

    return {};
}

int main()
{
    Color apple { green };
    Color raspberry { Color::blue };

    State::State state { State::run };

    if (state == State::run)
        std::cout << "Your state is run!\n";
    else
        std::cout << "Your state isn't run!\n";
    
    Animals anim {};
    std::cout << anim << '\n'; // prints 0

    anim = static_cast<Animals>(-1); // pig

    Spec sp { 1 }; // ok: can brace initialize unscoped enumeration with specified base with integer (C++17)

    // Working with strings
    std::cout << "Enter a pet: parrot, fox, cow: ";
    std::string s{};
    std::cin >> s;

    std::optional<Pets> pet { getPetFromString(s) };
    
    if (!pet)
        std::cout << "You entered an invalid pet\n";
    else
        std::cout << "You entered: " << getPetName(*pet) << '\n';

    return 0;
}
