#include <iostream>
#include <functional>

int foo()
{
    return 5;
}

int goo()
{
    return 10;
}

int hoo(int x)
{
    return x;
}

bool ascending(int x, int y)
{
    return x < y ? true : false;
}

bool descending(int x, int y)
{
    return x > y ? true : false;
}

void selectionSort(int* array, int size, bool (*comparsionFunc)(int, int) = ascending ) // with a default ascending() param
{

    for (int startIndex{0}; startIndex < size - 1; ++startIndex)
    {
        int smallestIndex{ startIndex };

        for ( int currentIndex{ startIndex + 1 }; currentIndex < size; ++currentIndex )
        {
            if ( (*comparsionFunc)(array[currentIndex], array[smallestIndex]) ) // Callback function call
            smallestIndex = currentIndex;
        }

        std::swap(array[startIndex], array[smallestIndex]);
    }
}

using ComparsionFunc = bool(*)(int, int); // It's better to make an alias

void selectionSort_notUgly(int* array, int size, ComparsionFunc func); // clean

void selectionSort_function(int* array, int size, std::function<bool(int, int)> func); // function from <functional> header

using ComparsionFunctional = std::function<bool(int,int)>; // the same - an alias

void printArray(int* array, int size)
{
    for ( std::size_t index{0}; index < size; ++index )
        std::cout << array[index] << ' ';
}

int main()
{
    int (*fncPtr)(){ &foo }; // fncPtr points to function foo()
    fncPtr = &goo; // fcnPtr now points to function goo

    std::function<int()> fncF1 { &foo }; // using <functional>
    std::function fncF2 { &foo };
    auto fncF3{ &foo };

    int (*fncPtr1)(int){ &hoo }; // parameters must match the function hoo(int)

    if (fncPtr1) // make sure fncPtr1 isn't a null ptr
    {
        std::cout << (*fncPtr1)(20) << '\n'; // call to hoo(20)
        std::cout << fncPtr1(30) << '\n'; // modern call to hoo(20) 
    }

    int array[]{ 10, 2, 5, 3, 9, 8, 45, 6 };

    selectionSort(array, std::size(array), ascending); // passing ascending() func through pointer
    printArray(array, std::size(array));

    std::cout << '\n';

    selectionSort(array, std::size(array), descending); // passing descending() func through pointer
    printArray(array, std::size(array));

    return 0;
}
