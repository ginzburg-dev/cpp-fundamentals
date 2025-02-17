#include <iostream>

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

// Use an 8-bit integer as the enum underlying type
enum Spec : std::int8_t
{
    spec1,
    spec2,
};

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
    std::cout << anim; // prints 0
    return 0;
}
