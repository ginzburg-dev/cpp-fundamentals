#include <iostream>


// A Smart pointer is a composition class that is designed to manage dynamically allocated memory 
// and ensure that memory gets deleted when the smart pointer object goes out of scope.

// The main idea behind move semantic is to avoid having 2 smart pointers owning the same object,
// because that would cause undefined behavour when they both try to destroy it.

template <typename T>
class Auto_ptr
{
private:
    T* m_ptr{};

public:
    Auto_ptr(T* ptr=nullptr)
        : m_ptr{ ptr }
    {}

    ~Auto_ptr()
    {
        delete m_ptr;
    }

    // A copy constructor that implements move semantics
    Auto_ptr(Auto_ptr& a)
    {
        m_ptr = a.m_ptr;
        a.m_ptr = nullptr;
    }

    // An assignment operator that implements move semantics
    Auto_ptr& operator= (Auto_ptr& a)
    {
        if ( &a == this )
            return *this;
        
        delete m_ptr;
        m_ptr = a.m_ptr;
        a.m_ptr = nullptr;
        return *this;
    }

    T& operator*() const { return *m_ptr; }
    T* operator->() const { return m_ptr; }
    T* getPtr() const { return m_ptr; }
    bool isNull() const { return m_ptr == nullptr; }
};

class Resource
{
public:
    Resource() { std::cout << "Resource constructor.\n"; }
    ~Resource() { std::cout << "Resource destructor.\n"; }
    void printHi() { std::cout << "Hi\n"; }
};

int main()
{
    Auto_ptr<Resource> res1(new Resource());
	Auto_ptr<Resource> res2; // Start as nullptr

	std::cout << "res1 is " << (res1.isNull() ? "null\n" : "not null\n");
	std::cout << "res2 is " << (res2.isNull() ? "null\n" : "not null\n");

	res2 = res1; // res2 assumes ownership, res1 is set to null

	std::cout << "Ownership transferred\n";

	std::cout << "res1 is " << (res1.isNull() ? "null\n" : "not null\n");
	std::cout << "res2 is " << (res2.isNull() ? "null\n" : "not null\n");

    return 0;
}
