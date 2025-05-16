#include "creature.h"
#include <iostream>
#include <memory>

int main()
{
    Creature monster{ "Shaun", {1, 2} };
    std::cout << monster << '\n';
    
    return 0;
}
