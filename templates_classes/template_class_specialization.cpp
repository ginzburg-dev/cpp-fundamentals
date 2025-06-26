#include <iostream>
#include <cstdint>

template<typename T>
class Storage8
{
private:
    T m_data[8]{};

public:
    void set(int index, const T& value) { m_data[index] = value; }
    const T& get(int index) const { return m_data[index]; }
};

// specialize a class
template<>
class Storage8<bool>
{
private:
    std::uint8_t m_data{};

public:
    void set(int index, bool value) 
    {
        // Figure out which bit we're setting/unsetting
        // This will put a 1 in the bit we're interested in turning on/off
        auto mask{ 1 << index };

        if (value) // If we're setting a bit
            m_data |= value; // use bitwise-or to turn that bit on 
        else // if we're turning a bit off
            m_data &= ~mask; // bitwise-and the inverse mask to turn that bit off
    }

    bool get(int index) const 
    {
        auto mask{ 1 << index };
        return (m_data & mask); 
    }
};

template<typename T>
class Storage
{
private:
    T m_value{};

public:
    Storage(const T& value)
        : m_value{value}
    {}

    void print() const
    {
        std::cout << m_value << '\n';
    }
};

// specialization of a class member
template<>
void Storage<double>::print() const // not explicitly 'inline'
{
    std::cout << std::scientific << m_value << '\n';
}

int main()
{
    Storage<double> storage{3.14};
    storage.print(); // Prints: 3.140000e+00

    return 0;
}
