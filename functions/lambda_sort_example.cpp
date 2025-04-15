#include <iostream>
#include <array>
#include <string_view>

struct Student
{
    std::string_view name{};
    int points{};
};

struct Season
{
    std::string_view name{};
    double averageTemperature{};
};

int main()
{
     // Example 1

    constexpr std::array<Student, 8> arr{
        {
            { "Albert", 3 },
            { "Ben", 5 },
            { "Christine", 2 },
            { "Dan", 8 },
            { "Enchilada", 4 },
            { "Francis", 1 },
            { "Greg", 3 },
            { "Hagrid", 5 }
        }
    };
    
    const auto best{
        std::max_element(arr.begin(), arr.end(), [](const auto& a, const auto& b){ return a.points < b.points; })
    };

    std::cout << "The best student " << best->name << " has " << best->points << " points.\n";

    // Example 2

    std::array<Season, 4> seasons{
        {
            { "Spring", 10.0 },
            { "Summer", 24.0 },
            { "Fall", 9.0 },
            { "Winter", -10.0 }
        }
    };

    std::sort(seasons.begin(), seasons.end(), 
        [](const auto& a, const auto& b){  
            return a.averageTemperature < b.averageTemperature;
    });

    for (const auto& i : seasons)
        std::cout << i.name << '\n';

    return 0;
}
