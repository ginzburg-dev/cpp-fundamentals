#include <iostream>
#include <algorithm>
#include <cstddef>
#include <string>

std::size_t getNameCount()
{
    std::cout << "How many names you would like to enter? ";
    std::size_t nNames{};
    std::cin >> nNames;

    return nNames;
}

void getNames(std::string* names, std::size_t length)
{
    for (std::size_t index {0}; index < length; ++index)
    {
        std::cout << "Enter name #" << index + 1 << ": ";
        std::getline(std::cin >> std::ws, names[index]);
    }
}

void printNames(std::string* names, std::size_t length)
{
    for (std::size_t index {0}; index < length; ++index)
        std::cout << names[index] << ' ';
    std::cout << '\n';
}

int main()
{
    std::size_t length { getNameCount() };

    auto* names{ new std::string[length]{} };
    
    getNames(names, length);

    std::sort(names, names + length);

    printNames(names, length);

    delete[] names;

    return 0;
}
