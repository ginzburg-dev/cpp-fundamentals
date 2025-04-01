#include <iostream>
#include <vector>
#include <ranges> // C++20 std::views::reverse
#include <string>

int main()
{
    std::vector arr { 1, 2, 3, 4, 5, 6, 7 };
    for ( auto num : arr )
        std::cout << num << ' ';
    
    std::cout << '\n';

    // For range-based for loops, prefer to define the element type as:
    // auto when you want to modify copies of the elements.
    // auto& when you want to modify the original elements.
    // const auto& otherwise (when you just need to view the original elements).

    std::vector<std::string_view> letters { "A", "B", "C", "D" };
    for (const auto& st : letters)
        std::cout << st << ' ';

    // for (const auto st : std::views::reverse(letters)) // C++20
    //     std::cout << st << ' ';

    return 0;
}
