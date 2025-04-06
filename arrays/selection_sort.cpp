#include <iostream>
#include <utility>

int main()
{
    int array[] { 100, 39, 2, 595, 3, 4 };

    constexpr int length { static_cast<int>(std::size(array)) };

    for (int startIndex{0}; startIndex < length - 1; ++startIndex)
    {
        int smallestIndex{ startIndex };

        for ( int currentIndex{ startIndex + 1 }; currentIndex < length; ++currentIndex )
        {
            if ( array[currentIndex] < array[smallestIndex] )
                smallestIndex = currentIndex;
        }

        std::swap(array[startIndex], array[smallestIndex]);
    }

    for ( std::size_t index{0}; index < std::size(array); ++index )
        std::cout << array[index] << ' ';

    std::cout << '\n';

    return 0;
}
