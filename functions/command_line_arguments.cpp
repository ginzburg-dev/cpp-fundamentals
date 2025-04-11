#include <cstddef>
#include <string>
#include <sstream>
#include <iostream>

int main(int argc, char* argv[])
{
    std::cout << "There are " << argc << " arguments.\n";
    
    for (std::size_t count{0}; count < argc; ++count)
    {
        std::cout << count << ' ' << argv[count] << '\n';
    }

    std::stringstream convert { argv[3] };

    int myint{};
    if ( !(convert >> myint) )
        myint = 0; // conversion fails
    
    std::cout << "My integer: " << myint << '\n';

    return 0;
}
