#include <algorithm> // for std::copy
#include <cassert> // for assert()
#include <initializer_list> // for std::initializer_list
#include <iostream>

class IntArray
{
private:
    int m_length{};
    int* m_data{};

public:
    IntArray() = default;

    IntArray(int length)
        : m_length{length}, m_data{ new int[static_cast<std::size_t>(length)]{} }
    {}

    IntArray(std::initializer_list<int> list)
        : IntArray(static_cast<int>(list.size()))
    {
        std::copy(list.begin(), list.end(), m_data);
    }

    ~IntArray()
    {
        delete[] m_data;
    }

    IntArray(const IntArray&) = delete; // to avoid shallow copies
    IntArray& operator=(std::initializer_list<int> list)
    {
        if ( m_length != list.size() )
        {
            m_length = static_cast<int>(list.size());
            delete[] m_data;
            m_data = new int[list.size()]{};
        }

        std::copy(list.begin(), list.end(), m_data);

        return *this;
    }

    int& operator[](int index)
    {
        assert(index >= 0 && index < m_length);
        return m_data[index];
    }

    int getLength() const { return m_length; }
};

int main()
{
    IntArray array{ 5, 4, 3, 2, 1 }; // initializer list
    for (int i{0}; i < array.getLength(); ++i)
        std::cout << array[i] << ' ';
    std::cout << '\n';

    // Accessing elements of a std::initializer_list

    std::initializer_list<int> list { 1, 2, 3, 4, 5 };

    // range-based for loop
    for (auto& i : list)
        std::cout << i << ' ';
    std::cout << '\n';

    // using the begin() member function to get an iterator
    for(std::size_t i{0}; i < list.size(); ++i)
    {
        std::cout << list.begin()[i] << ' ';
    }
    std::cout << '\n';

    // Testing an assignment operator

    array = { 1, 2, 3, 4, 5, 6, 7 };
    for (int i{0}; i < array.getLength(); ++i)
        std::cout << array[i] << ' ';
    std::cout << '\n';


    return 0;
}
