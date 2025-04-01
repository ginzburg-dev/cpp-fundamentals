#include <iostream>

int main()
{
    int ttt1[3][3]{};

    int ttt2[3][3]{
        { 1, 2, 3 }, // you can use another brackets for readibility
        { 4, 5, 6 },
        { 7, 8, 9 }
    };

    int ttt3[][3]{ // can ommit only the leftmost length specification
        { 1, 2 },
        { 1 },
        {}
    };

    // double for-loop
    for ( std::size_t row{0}; row < std::size(ttt3); ++row)
    {
        for ( std::size_t col{0}; col < std::size(ttt3[0]); ++col) // std::size(ttt3[0]) returns the number of columns
            std::cout << ttt3[row][col] << ' ';

            std::cout << '\n';
    }
    
    std::cout << '\n';

    // double range-based for-loop
    for ( const auto& i : ttt3 )
    {
        for ( const auto& e : i )
            std::cout << e << ' ';
        
        std::cout << '\n';
    }

    return 0;
}
