#include <iostream>
#include <cassert>

int binarySearch(const int* arr, int target, int min, int max)
{
    assert(arr);

    while( min <= max )
    {
        int midpoint { min + (max - min)/2 };

        if ( arr[midpoint] > target )
            max = midpoint - 1;
        else if ( arr[midpoint] != target )
            min = midpoint + 1;
        else
            return midpoint; 
    }

    return -1;
}

int binarySearchRecursive(const int arr[], int target, int min, int max)
{
    assert(arr);

    if ( min > max )
        return -1;

    int midpoint { min + (max - min)/2 };

    if ( arr[midpoint] > target )
        return binarySearchRecursive(arr, target, min, midpoint - 1);
    else if ( arr[midpoint] < target )
        return binarySearchRecursive(arr, target, midpoint + 1, max);

    return midpoint;
}

int main()
{
    constexpr int array[]{ 3, 6, 8, 12, 14, 17, 20, 21, 26, 32, 36, 37, 42, 44, 48 };
    constexpr int testValues[]{ 0, 3, 12, 13, 22, 26, 43, 44, 48, 49 };
    int expectedResult[]{ -1, 0, 3, -1, -1, 8, -1, 13, 14, -1 };


    static_assert( std::size(testValues) == std::size(expectedResult) );

    int numTestValues{ std::size(testValues) };
    for (int count{0}; count < numTestValues; ++count)
    {
        // int index{ binarySearch(array, testValues[count], 0, static_cast<int>(std::size(array) - 1)) };
        int index{ binarySearchRecursive(array, testValues[count], 0, static_cast<int>(std::size(array) - 1)) };
        if ( expectedResult[count] == index )
            std::cout << "test value " << testValues[count] << "passed!\n";
        else
            std::cout << "test value " << testValues[count] << "failed. There's something wrong with your code!\n";
    }

    return 0;
}
