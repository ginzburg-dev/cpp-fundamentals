#include <iostream>
#include <string>
#include <string_view>

int main()
{
    std::string str{ "I saw a red car yesterday." };
    
    str.replace(8, 3, "blue");
    
    std::cout << str << '\n'; // I saw a blue car yesterday.

    return 0;
}
