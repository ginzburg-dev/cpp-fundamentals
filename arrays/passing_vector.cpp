#include <iostream>
#include <vector>

template <typename T>
void passByRef(const std::vector<T>& arr) // vector type must be specified because deduce works only from initizers
{
    std::cout << arr[0] << '\n';
}

template <typename T>
void passByRef2(const T& arr) // ok: will accept any type of objects that has an overloaded operator[]
{
    std::cout << arr[0] << '\n';
}

void passByRefAbbr(const auto& arr) // C++20 abbreviated function template
{
    std::cout << arr[0] << '\n';
}

int main()
{
    std::vector array1 { 1, 2, 3, 4, 5 };
    passByRef(array1);
    passByRefAbbr(array1);
    
    std::vector array2 { 1.1, 2.2, 3.3 };
    passByRef(array2);
    passByRef2(array2);
    passByRefAbbr(array2);

    return 0;
}
