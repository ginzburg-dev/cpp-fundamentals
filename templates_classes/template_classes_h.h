#ifndef TEMPLATE_CLASSES_H_H
#define TEMPLATE_CLASSES_H_H

#include <cassert>
#include <cstddef>
#include <iostream>

template<typename T>
class TemplateClass
{
private:
    T* m_data{};
    std::size_t m_length{};

public:
    TemplateClass(int length)
        : m_data{ new T[length]{} }, m_length{static_cast<std::size_t>(length)}
    {}

    TemplateClass(const TemplateClass&) = delete;
    TemplateClass& operator=(const TemplateClass&) = delete;

    struct Iterator
    {
        T* ptr;
        bool operator!=(const Iterator& other) const { return ptr != other.ptr; }
        T& operator*() { return *ptr; }
        Iterator& operator++() { ++ptr; return *this; }
    };

    Iterator begin() { return Iterator{m_data}; }
    Iterator end() { return Iterator{m_data + m_length}; }

    void erase()
    {
        delete[] m_data;
        m_data = nullptr;
        m_length = 0;
    }
    
    T& operator[](int index);

    void inlMethod() const;

    int getLength() const { return static_cast<int>(m_length); }

    ~TemplateClass(){ delete[] m_data; }
};

// You can't put the defenition to the separate .cpp, 
// because template semantic require all definition in one place to see all definitions, 
// unless you put a definition in .inl file and include it at the bottom of the header.

template<typename T>
T& TemplateClass<T>::operator[](int index) // No 'inlide' keyword needed. It doesn't violate the ODR; instancing the template creates a unique copy in each translation unit.
{
    assert(index >= 0 && index < m_length);
    return m_data[index];
}

inline void nonTemplateFunction()
{
    std::cout << "Non-template function: 'inline' is required to avoid violating the ODR.\n";
}

#include "template_classes_h.inl" // you can put the defenition of the method inside .inl file if you want to separate it from .h

#endif


// Or the third method - 
// templates.cpp
// // Ensure the full Array template definition can be seen
// #include "Array.h"
// #include "Array.cpp" // we're breaking best practices here, but only in this one place

// // #include other .h and .cpp template definitions you need here

// template class Array<int>; // Explicitly instantiate template Array<int>
// template class Array<double>; // Explicitly instantiate template Array<double>
