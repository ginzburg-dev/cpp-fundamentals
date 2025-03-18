#include <iostream>
#include <vector>
#include <cassert>
#include <type_traits> // for std::underlying_type_t

namespace Students
{
    enum Name : unsigned int // specify if you use non-constexpr Name enum
    {
        kenny, // 0
        kyle, // 1
        stan, // 2
        butters, // 3
        cartman, // 4
        // add future enumerators here
        max_students // 5
    };
}

// enum class doesn't have an implicit convertion to int
enum class StudentNames
{
    kenny, // 0
    kyle, // 1
    stan, // 2
    butters, // 3
    cartman, // 4
    // add future enumerators here
    max_students // 5
};

constexpr auto operator+(StudentNames a) noexcept
{
    return static_cast<std::underlying_type_t<StudentNames>>(a); // std::underlying_type_t<T> designed especially for enums
}

int main()
{
    std::vector<int> testScores(Students::max_students);

    testScores[Students::stan] = 76;

    std::cout << "Max students " << Students::max_students << '\n';

    std::vector<int> arr(5);
    assert(std::size(arr) == Students::max_students);

    arr[static_cast<int>(StudentNames::butters)] = 67; // use static_cast to explicitly convert enum class type into int
    arr[+StudentNames::butters] = 68;

    return 0;
}
