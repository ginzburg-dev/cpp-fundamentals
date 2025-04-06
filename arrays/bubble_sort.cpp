#include <iostream>
#include <utility> // for std::swap()

int main()
{
    int array[]{ 6, 3, 2, 9, 7, 1, 5, 4, 8 };

    constexpr int length{ static_cast<int>(std::size(array)) };

    for ( int iteration{0}; iteration < length-1; ++iteration)
    {
        bool swapped = false;

        for ( int index{0}; index < length - iteration - 1; ++index)
            if ( array[index] > array[index+1] )
            {
                std::swap(array[index], array[index+1]);
                swapped = true;
            }
        
        if ( !swapped )
        {
            std::cout << "An array was sorted in " << iteration+1 << " iterations.\n";
            break;
        }
    }

    for ( int index{0}; index < length; ++index)
        std::cout << array[index] << ' ';

    std::cout << '\n';

    return 0;
}
