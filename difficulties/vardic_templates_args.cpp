#include <cstddef>
#include <iostream>
#include <utility>

void print()
{
    std::cout << "Base case" << '\n';
}

template<typename T, typename... Args>
void print(T&& first, Args&&... args)
{
    std::cout << first << ' ';
    print(args...);
}

template<typename... Args>
void print2(Args&&... args)
{
    std::size_t n{0}; // Counter
    ((std::cout << (n++ ? " " : "") << std::forward<Args>(args)), ...);
    std::cout << '\n';
}

template<typename... Args>
void print3(Args&&... args)
{
    auto out = [&](auto&&... args){
        ((std::cout <<  std::forward<Args>(args) << ' '), ...);
        std::cout << '\n';
    };
    out(args...);
}

int main()
{
    print(1, 2.2, "string", '4');
    print2(2, 5.5, "string2", 'n');
    print3(3, 7.5, "string3", 't');
    return 0;
}
