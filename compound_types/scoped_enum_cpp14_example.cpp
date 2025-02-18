#include <iostream>
#include <string>
#include <string_view>

enum class Animals
{
    pig, 
    chicken, 
    goat, 
    cat, 
    dog, 
    duck,
};

constexpr std::string_view getAnimalName(Animals animal)
{
    switch (animal)
    {
    case Animals::cat:
        return "cat";
    case Animals::chicken:
        return "chicken";
    case Animals::dog:
        return "dog";
    case Animals::duck:
        return "duck";
    case Animals::goat:
        return "goat";
    case Animals::pig:
        return "pig";
    default:
        return "???";
    }
}

void printNumberOfLegs(Animals animal)
{
    std::cout << "A " << getAnimalName(animal) << " has ";

    switch (animal)
    {
    case Animals::cat:
    case Animals::dog:
    case Animals::pig:
    case Animals::goat:
        std::cout << 4;
        break;
    case Animals::chicken:
    case Animals::duck:
        std::cout << 2;
        break;
    default:
        std::cout << "Invalid animal";
        break;
    }

    std::cout << " legs.\n";
}

int main()
{
    printNumberOfLegs(Animals::cat);
    printNumberOfLegs(Animals::chicken);

    return 0;
}
