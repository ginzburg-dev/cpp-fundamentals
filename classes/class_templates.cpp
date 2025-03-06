#include <iostream>

template <typename T>
struct Pair
{
    T first{};
    T second{};
};

// Here's a deduction guide for our Pair (required in C++17 or older)
// Pair objects initialized with arguments of type T and T should deduce to Pair<T>
template <typename T>
Pair(T, T) -> Pair<T>;

template <typename T>
class Data
{
private:
    T m_data1{};
    T m_data2{};

public:
    Data(const T& data1, const T& data2) // const ref in case the data is too expensive to copy
        : m_data1 { data1 }
        , m_data2 { data2 }
    {
    }

    const T& getData1() const { return m_data1; }
    const T& getData2() const { return m_data2; }

    bool isEqual(const Data<T>& data); // Because this is a definition for a member function of Pair<T>, we’re in the scope of the Pair<T> class template. Therefore, any use of Pair is shorthand for Pair<T>
    
    template <typename U>
    bool isEqual(const Data<U>& data); // overload with different type of data
};

// When we define a member function outside the class definition,
// we need to resupply a template parameter declaration
// we noted that CTAD doesn’t work with function parameters (as it is argument deduction, not parameter deduction). 
// However, using an injected class name as a function parameter is okay, 
// as it is shorthand for the fully templated name, not a use of CTAD.
// Any member function templates defined outside the class definition 
// should be defined just below the class definition (in the same file).

template <typename T>
bool Data<T>::isEqual(const Data& data)
{
    return ( m_data1 == data.m_data1 )&&( m_data2 == data.m_data2 );
}

template <typename T> // No second template parameter here!
template <typename U>
bool Data<T>::isEqual(const Data<U>& data)
{
    return ( m_data1 == data.getData1() )&&( m_data2 == data.getData2() );
}

int main()
{
    Pair<double> p1 { 1.0, 2.0 };
    Pair p2 { 3, 4 };

    Data data1 { 1, 2 };
    Data data2 { 1, 2 };
    Data data3 { 1.0, 2.0 };

    std::cout << "Is Equal: " << data1.isEqual(data2) << '\n';
    std::cout << "Is Equal: " << data1.isEqual(data3) << '\n'; // compare different types int and double

    return 0;
}
