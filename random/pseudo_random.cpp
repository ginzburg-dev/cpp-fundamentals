#include <iostream>

unsigned int LCG16()
{
    static unsigned int s_state{ 0 }; // only initialized the first time this function is called

    s_state = 8723623 * s_state + 2493293;

    return s_state % 32523;
}

int main()
{
    for (int i{ 0 }; i <= 100; ++i)
    {
        std::cout << LCG16() << " ";
    }
    
    return 0;
}
