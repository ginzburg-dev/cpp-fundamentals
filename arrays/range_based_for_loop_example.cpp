#include <iostream>
#include <string>
#include <vector>

std::string getName()
{
    std::cout << "Enter a name: ";
    std::string name{};
    std::cin >> name;

    return name;
}

template <typename T>
bool isValueInArray(const std::vector<T>& arr, const T& input)
{
    for (const auto& name : arr )
    {
        if (input == name)
        {
            return true;
        }
    }

    return false;
}

int main()
{
    std::vector<std::string_view> names {"Alex", "Betty", "Caroline", "Dave", "Emily", "Fred", "Greg", "Holly" };
    std::string input { getName() };

    if ( isValueInArray<std::string_view>(names, input) )
        std::cout << input << " was found.\n";
    else
        std::cout << input << " wasn't found.\n";
        
    return 0;
}
