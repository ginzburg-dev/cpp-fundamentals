#include <cstdlib> // for std::exit()
#include <iostream>

void cleanup()
{
    // code here to do any kind of cleanup required
    std::cout << "cleanup!\n";
}

int main()
{
    std::atexit(cleanup);

    std::cout << 1 << '\n';

    std::exit(0); // terminate and return status 0 to operating system

    // following statment never executes
    std::cout << 2 << '\n';

    return 0;
}
