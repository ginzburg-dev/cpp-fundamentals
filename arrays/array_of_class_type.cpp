#include <iostream>
#include <array>

struct Object
{
    int first{};
    int second{};
    int third{};
};

template <typename T, std::size_t N>
void printArray(const std::array<T, N>& arr)
{
    for ( const auto& i : arr )
    {
        std::cout << "( " << i.first << ' ' << i.second << ' ' << i.third << " )\n";
    }
}

int main()
{
    std::array<Object, 3> obj1 {};
    obj1[0] = { 1, 2, 3 };
    obj1[1] = { 4, 5, 6 };
    obj1[2] = { 7, 8, 9 };

    constexpr std::array obj2 { // CTAD to deduce template arguments <Object, 3>
        Object{ 1, 2, 3 },
        Object{ 4, 5, 6 },
        Object{ 7, 8, 9 }
    };

    constexpr std::array<Object, 3> obj3 {{ // extra set of braces to initialize the C-style array member
        { 1, 2, 3 },
        { 4, 5, 6 },
        { 7, 8, 9 }
    }};

    constexpr std::array objExample{
        Object{ 1, 2, 3 },
        Object{ 4, 5, 6 },
        Object{ 7, 8, 9 },
    };
    printArray(objExample);

    constexpr std::array<Object, 3> objExample1{{
        { 1, 2, 3 },
        { 4, 5, 6 },
        { 7, 8, 9 },
    }};
    printArray(objExample1);

    return 0;
}
