#include <iostream>
#include <cstddef>
#include <cassert>

class IntArray
{
private:
    int* m_data{};
    int m_length{};

public:
    explicit IntArray(int length=0)
    {
        assert(length >= 0 && "Length must be non-negative");

        if ( length < 0 )
        {
            std::cerr << "Warning: the length is negative.\n";
            length = 0;
        }
        
        m_length = length;
        m_data = new int[static_cast<std::size_t>(m_length)] ;
    }

    IntArray(const IntArray& source)
    {
        deepCopy(source);
    }

    ~IntArray()
    {
        delete[] m_data;
    }

    void deepCopy(const IntArray& source);

    IntArray& operator= (const IntArray& array)
    {
        if ( this != &array )
        {
            deepCopy(array);
        }

        return *this;
    }

    int& operator[] (const int index)
    {
        assert( ( index >= 0 && index < m_length ) && "Index is out of range");
        return m_data[index];
    }

    friend std::ostream& operator<< (std::ostream& out, const IntArray& array);  
};

void IntArray::deepCopy(const IntArray& source)
{
    m_length = source.m_length;
    delete[] m_data;
    if (source.m_data)
    {
        m_data = new int[static_cast<std::size_t>(m_length)];

        for (int i{0}; i < m_length; ++i)
            m_data[i] = source.m_data[i];
    }
    else
        m_data = nullptr;
}

std::ostream& operator<< (std::ostream& out, const IntArray& array)
{
    for (int i{0}; i < array.m_length; ++i)
        out << array.m_data[i] << ' ';
    return out;
}

IntArray fillArray()
{
	IntArray a(5);

	a[0] = 5;
	a[1] = 8;
	a[2] = 2;
	a[3] = 3;
	a[4] = 6;

	return a;
}

int main()
{
    IntArray a{ fillArray() };

	std::cout << a << '\n';

	auto& ref{ a }; // we're using this reference to avoid compiler self-assignment errors
	a = ref;

	IntArray b(1);
	b = a;

	a[4] = 7;

	std::cout << b << '\n';

    return 0;
}
