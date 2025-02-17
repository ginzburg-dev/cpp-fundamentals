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
        idle,
        walk,
        run,
        jump,
    };
    
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
    
    return 0;
}
