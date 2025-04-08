#include <iostream>
#include <cassert>
#include <cstddef>

class IntArray
{
private:
    int* m_array{};
    int m_length{};

public:
    IntArray(int length)
    {
        assert( length > 0 );

        m_array = new int[static_cast<std::size_t>(length)]{};
        m_length = length;
    }

    int& operator[](int index)
    {
        return m_array[index];
    }

    ~IntArray()
    {
        delete[] m_array;
    }
};

int main()
{
    return 0;
}
