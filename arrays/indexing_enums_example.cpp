#include <iostream>
#include <vector>

namespace Animals
{
    enum Animals
    {
        chicken,
        dog,
        cat,
        elephant,
        duck,
        snake,
        max_names,
    };

    const std::vector<int> legs { 2, 4, 4, 4, 2, 0 };
}

int main()
{
    assert ( std::size(Animals::legs) == Animals::max_names );

    std::cout << "Elephant has " << Animals::legs[Animals::elephant] << '\n';
    
    return 0;
}
