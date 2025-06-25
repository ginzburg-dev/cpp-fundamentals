#include <iostream>

// A template non-type parameter is a template parameter where the type of the parameter is 
// predefined and is substituted for a constexpr value passed in as an argument.
//
// A non-type parameter can be any of the following types:
// 
// An integral type
// An enumeration type
// A pointer or reference to a class object
// A pointer or reference to a function
// A pointer or reference to a class member function   
// std::nullptr_t                  
// A floating point type (since C++20)                         

template<typename T, int size>
class StaticArray
{
private:
    T m_array[size]{};
public:
    T* getArray();

    T& operator[](int index){ return m_array[index]; }
};

template<typename T, int size>
T* StaticArray<T, size>::getArray()
{
    return m_array;
}

int main()
{
    StaticArray<int, 4> staticArray{};
    for (int i = 0; i < 4; ++i)
        staticArray[i] = i;
    
    for (int i = 0; i < 4; ++i)
        std::cout << staticArray[i] << ' ';
    std::cout << '\n';

    return 0;
}
