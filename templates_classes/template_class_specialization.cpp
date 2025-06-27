#include <iostream>
#include <cstdint>
#include <memory>
#include <array>

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

// Partial specialization

template<typename T, int size>
class StoragePartial
{
private:
    T m_data[size];

public:
    void set(int index, const T& value){ m_data[index] = value; }
    const T& get(int index) const { return m_data[index]; }
};

// Partial specialization of a class
template<int size>
class StoragePartial<double, size>
{
private:
    double m_data[size];

public:
    void set(int index, const double& value){ m_data[index] = value; }
    const double& get(int index) const { return m_data[index]; }
};

// Partial specialization is allowed only as a class based, not class' methods or functions
template<int size>
void printPartial(const StoragePartial<double, size>& storage)
{
    for(int i = 0; i < size; ++i)
        std::cout << std::scientific << storage.get(i) << ' ';
}

// Partial specialization for pointers
template<typename T, int size>
class StoragePartial<T*, size>
{
private:
    std::array<std::unique_ptr<T>, size> m_data{};

public:
    void set(int index, const T& value){ m_data[index] = std::make_unique<T>(value); }
    const T& get(int index) const { return *m_data[index]; }
};


int main()
{
    Storage<double> storage{3.14};
    storage.print(); // Prints: 3.140000e+00

    StoragePartial<double*, 1> ptrStoragePartial{};
    ptrStoragePartial.set(0, 10.4);
    std::cout << ptrStoragePartial.get(0) << '\n';

    return 0;
}
