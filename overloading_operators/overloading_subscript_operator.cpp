#include <iostream>
#include <cstddef>
#include <cassert>
#include <string_view>

class List
{
private:
    int m_list[10]{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };;

public:
    int& operator[](int index) { return m_list[index]; }
    const int& operator[](int index) const { return m_list[index]; }
};

// Example 2. How to avoid duplicating logic in [] overloading in both non-cons and const versions
class List2
{
private:
    int m_list[10]{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };;

public:
    int& operator[](int index) 
    { 
        // Call the const [] overloading to prevent duplicatting in logic. 
        // All logic such as bounds checking can be implemented in the const version.
        return const_cast<int&>(std::as_const(*this)[index]); 
    }
    const int& operator[](int index) const 
    {
        // This is some logic that we don't want to duplicate
        if ( index < 0 || index >= 10 ) 
            throw std::out_of_range("Out of range");

        return m_list[index]; 
    }
};

// Example 3. Version with assert
class List3
{
private:
    int m_list[10]{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };;

public:
    int& operator[](int index) 
    {
        return const_cast<int&>(std::as_const(*this)[index]); 
    }
    const int& operator[](int index) const 
    {
        // This is some logic that we don't want to duplicate
        assert(index >= 0 && static_cast<std::size_t>(index) < std::size(m_list));

        // or if we don't want to use assert
        if ( !(index >= 0 && static_cast<std::size_t>(index) < std::size(m_list)) )
        {
            // hadle invalid index here
        }

        return m_list[index]; 
    }
};

class Stupid
{
private:
public:
    void operator[](std::string_view string); // The function parameter does not need to be an integral type
};

void Stupid::operator[](std::string_view string)
{
    std::cout << string << '\n';
}

int main()
{
    List2 list{};
    list[3] = 10;

    std::cout << list[3] << '\n';

    const List2 clist{};
    
    std::cout << clist[3] << '\n';

    List3* ptr_list{ new List3 };
    // ptr_list[0] = 100; // Error. This will assume we're accessing index 0 of an array of List3
    (*ptr_list)[0] = 100;

    std::cout << (*ptr_list)[0] << '\n';

    Stupid stupid{};
    stupid["Ugly"]; // print "Ugly"

    return 0;
}
