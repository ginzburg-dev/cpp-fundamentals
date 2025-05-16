#include "creature.h"
#include <iostream>
#include <memory>

// A good rule of thumb is that each class should be built to accomplish a single task. 
// That task should either be the storage and manipulation of some kind of data (e.g. Point2D, std::string), 
// OR the coordination of its members (e.g. Creature). Ideally not both.

int main()
{
    Creature monster{ "Hiss", {1, 2} }; // Creature composed of Poin2D class and std::string
    std::cout << monster << '\n';

    return 0;
}
