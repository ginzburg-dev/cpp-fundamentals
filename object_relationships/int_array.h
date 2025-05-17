#ifndef INT_ARRAY_H
#define INT_ARRAY_H

#include <algorithm> // for std::copy_n
#include <cassert> // for assert()
#include <cstddef> // for std::size_t

class IntArray
{
private:
    int m_length{};
    int* m_data{};

public:
    IntArray() = default;

    IntArray(int length)
        : m_length{length}
    {
        assert(length >= 0);

        if (length > 0)
            m_data = new int[static_cast<std::size_t>(length)]{};
    }

    ~IntArray()
    {
        delete[] m_data;
    }

    IntArray(const IntArray& arr) 
        : IntArray(arr.getLength())
    {
        std::copy_n(arr.m_data, arr.m_length, m_data);
    }

    IntArray& operator=(const IntArray& arr)
    {
        if ( &arr == this )
            return *this;
        
        reallocate(arr.getLength());
        std::copy_n(arr.m_data, m_length, m_data);
        
        return *this;
    }

    void erase()
    {
        delete[] m_data;

        m_data = nullptr;
        m_length = 0;
    }

    int& operator[](int index)
    {
        assert(index >= 0 && index < m_length);
        return m_data[index];
    }

    int getLength() const { return m_length; }

    void reallocate(int newLength)
    {
        erase();

        if (newLength <= 0)
            return;
        
        m_data = new int[static_cast<std::size_t>(newLength)];
        m_length = newLength;
    }

    void resize(int newLength)
    {
        if ( m_length == newLength )
            return;
        
        if ( newLength <= 0 )
        {
            erase();
            return;
        }

        int* data{ new int[static_cast<std::size_t>(newLength)] };

        if ( m_length > 0 )
        {
            int elementsToCopy{ (newLength > m_length) ? m_length : newLength };
            std::copy_n(m_data, elementsToCopy, data);
        }

        delete[] m_data;
        m_data = data;
        m_length = newLength;
    }

    void insertBefore(int value, int index)
    {
        assert(index >= 0 && index <= m_length);

        int* data{ new int[static_cast<std::size_t>(m_length+1)] };

        std::copy_n(m_data, index, data);

        data[index] = value;

        std::copy_n(m_data + index, m_length - index, data + index + 1);

        delete[] m_data;
        m_data = data;
        ++m_length;
    }

    void remove(int index)
    {
        assert(index >= 0 && index < m_length);

        if (m_length == 1)
        {
            erase();
            return;
        }

        int* data{ new int[static_cast<std::size_t>(m_length-1)] };

        std::copy_n(m_data, index, data);
        std::copy_n(m_data + index + 1, m_length - index - 1, data + index);

        delete[] m_data;
        m_data = data;
        --m_length;
    }

    void insertAtBeginning(int value) { insertBefore(value, 0); }
    void insertAtEnd(int value) { insertBefore(value, m_length); }
};

#endif
