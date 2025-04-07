#include <cstddef>
#include <iostream>

int main()
{
    int* array1 = new int[5]{};
    int* array2 = new int[5]{ 1, 2, 3, 4, 5};
    int* array3{ new int[5]{} };
    int* array4{ new int[5]{ 1, 2, 3, 4, 5} };
    int* array5{ new int[]{ 1, 2, 3, 4, 5} }; // But there's no way to get the length in this case.

    auto* array6{ new int[5]{} };

    std::cout << "Enter the size of the array: ";
    std::size_t length{};
    std::cin >> length;

    int* array{ new int[length]{} }; // Now we're able to set the length of the array at runtime

    array[0] = 5;

    delete[] array; // use array delete to deallocate array

    return 0;
}
