#include "static_member_function.h"
#include <iostream>

struct Chars
{
    char first{};
    char second{};
    char third {};
};

class Simple
{
private:
    static inline int s_id { 1 };

    static Chars generate()
    {
        Chars c{};
        c.first = 'a';
        c.second = 'c';
        c.third = 'b';

        return c;
    }
public:
    static int getNextID();

    static int s_i;

    static inline Chars s_char { 'a', 'b', 'c' };

    static inline Chars s_charGen { generate() };
};

int Simple::getNextID() { return s_id++; }

int Simple::s_i { 1 };

int main()
{
    for (int i{ 1 }; i < 5; ++i )
        std::cout << "Next ID: " << Simple::getNextID() << '\n';
    
    std::cout << Simple::s_i << '\n';

    for (int i{ 1 }; i < 5; ++i )
        std::cout << "Next Header ID: " << SimpleHeader::getNextID() << '\n';
    
    return 0;
}
