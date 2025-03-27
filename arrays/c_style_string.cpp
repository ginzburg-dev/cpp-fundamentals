#include <iostream>
#include <cstring> // for std::strlen

void printCString(const char str[])
{
    while (*str != '\0')
    {
        std::cout << *str;
        ++str;
    }
}

void printCStringBackwards(const char str[])
{
    const char* ptr{ str };

    while (*ptr != '\0')
        ++ptr;

    while ( ptr-- != str )
    {
        std::cout << *ptr;
    }
}

int main()
{
    const char str1[]{ "String1" }; // 7 characters + null terminator '\0'
    constexpr char str2[]{ "String2" };
    const char* str3 { "String3" };
    std::cout << str1 << ' ' << str2 << ' ' << str3 << '\n';
    
    char str4[255];
    std::cout << "Enter your rolls: ";
    std::cin.getline(str4, std::size(str4));
    std::cout << "You entered: " << str4 << '\n';

    str4[0] = 'P';
    std::cout << str4 << '\n';

    // Length of teh C-style string
    char str5[]{ "Get the length!" };
    std::cout << "Length = " << std::size( str5 ) << ' ' << std::ssize( str5 ) << '\n'; // The length + null terminator

    char* str5_ptr { str5 }; // decay to char*
    //std::cout << std::size(str5_ptr);  // compile error: 
    std::cout << std::strlen(str5_ptr) << '\n'; // just the length without any null terminators. header <cstring>

    const char str6[]{ "Print it!" };
    printCString(str6);
    printCStringBackwards(str6);
    
    return 0;
}
