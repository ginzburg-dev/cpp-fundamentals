#include <iostream>

#define COLOR_RESET     "\033[0m"
#define COLOR_GREEN     "\033[1;32m"
#define COLOR_RED       "\033[31m"
#define COLOR_YELLOW    "\033[1;33m"
#define COLOR_MAGENTA   "\033[35m"

int main()
{
    std::cout << COLOR_GREEN << " LOG [GREEN]" << COLOR_RESET<< '\n';
    std::cout << COLOR_RED << " LOG [RED]" << COLOR_RESET << '\n';
    std::cout << COLOR_YELLOW << " LOG [YELLOW]" << COLOR_RESET << '\n';
    std::cout << COLOR_MAGENTA << " LOG [MARGENTA]" << COLOR_RESET << '\n';

    return 0;
}
