#include <iostream>
#include <vector>
#include <string>
#include <string_view>
#include <cassert>
#include <limits>
#include <utility>

namespace Items
{
    enum Type
    {
        healthPotion,
        torch,
        arrow,
        max_props,
    };
}

int countTotalItems(const std::vector<int>& props)
{
    int sum { 0 };
    for ( const auto& e : props )
        sum += e;
    return sum;
}

template <typename T>
std::pair<T,T> getMin(const std::vector<T>& arr )
{
    std::pair<T,T> p { 0, arr[0] };
    for (std::size_t i{0}; i < arr.size(); ++i)
    {
        if ( arr[i] < p.second )
        {
            p.first = i;
            p.second = arr[i];
        }
    }

    return p;
}

template <typename T>
std::pair<T,T> getMax(const std::vector<T>& arr )
{
    std::pair<T,T> p { 0, arr[0] };
    for (std::size_t i{0}; i < arr.size(); ++i)
    {
        if ( arr[i] > p.second )
        {
            p.first = i;
            p.second = arr[i];
        }
    }

    return p;
}

template <typename T>
void printArray(const std::vector<T>& arr)
{
    std::cout << "With array ( ";
    for ( const auto& i : arr )
        std::cout << i << ' ';
        std::cout << "):\n";

    std::pair<T,T> min { getMin(arr) };
    std::cout << "The min element has index " << min.first << " and value " << min.second << '\n';

    std::pair<T,T> max { getMax(arr) };
    std::cout << "The max element has index " << max.first << " and value " << max.second << '\n';
}

std::vector<int> getInputArray()
{
    std::cout << "Enter numbers to add ( use -1 to stop ): ";
    std::vector<int> v{};

    while (true)
    {
        int input{};
        std::cin >> input;

        if ( !std::cin )
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
            continue;
        }
        
        if ( input == -1 )
            return v;

        v.push_back(input);
    }
}

using namespace std::literals::string_view_literals;

int main()
{
    std::vector evens { 2, 4, 6, 8, 10, 12 };
    const std::vector doubles { 1.2, 3.4, 5.6, 7.8 };
    const std::vector strings { "Alex"sv, "Brad"sv, "Charles"sv, "Dave"sv };
    std::vector single { 12 };
    std::vector<int> twelves (12);
    std::cout << twelves.size() << '\n';

    std::vector props { 1, 5, 10 };
    std::vector propsNames { "health potion"sv, "torche"sv, "arrow"sv };

    assert( Items::max_props == std::size( props ) &&  "Vecor size doesn't fit to max_props" );

    for (std::size_t index{ 0 }; index < Items::max_props; ++index)
        std::cout << "You have " << props[index] << ' ' << propsNames[index] <<  ( props[index] > 1 ? "s" : "" ) << '\n';

    std::cout << "You have " << countTotalItems(props) << " total items\n";

    std::vector v1 { 3, 8, 2, 5, 7, 8, 3 };
    std::vector v2 { 5.5, 2.7, 3.3, 7.6, 1.2, 8.8, 6.6 };
    printArray(v1);
    printArray(v2);

    std::cout << '\n';

    std::vector<int> v3 { getInputArray() };
    printArray(v3);
    
    return 0;
}
