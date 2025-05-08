#include <iostream>
#include <string>
#include <string_view>

// Move Semantics Recap:
// When assigning or constructing from an l-value, we must copy since it may be used again.
// When assigning or constructing from an r-value (a temporary), we can move — transferring resources safely and efficiently.
// R-value references (T&&) introduced in C++11 allow us to distinguish these cases and optimize performance.

// The default implicit move constructor / assing operator does not know how to "steal" raw pointers — it simply copies them.
// We only need to manually implement move operations if:
//    We have raw pointers and want to transfer ownership.
//    We want custom behavior on move.
//    We have a destructor or copy functions, which disables the implicit move generation.

// Conditions for implicit move constructor/assignment generation:
//        1. No user-defined copy constructor
//        2. No user-defined copy assignment operator
//        3. No user-defined move constructor
//        4. No user-defined move assignment operator
//        5. No user-defined destructor
//
// If any of the above are explicitly declared, the compiler will not generate 
// the move constructor or move assignment operator for us 
// unless we explicitly request it with = default.

// Recapping copy constructors and copy assignment. Inefficient, but at least it doesn’t crash!
template <typename T>
class Auto_ptr3
{
private:
    T* m_ptr{};

public:
    Auto_ptr3(T* ptr=nullptr)
        : m_ptr{ptr}
    {}

    ~Auto_ptr3()
    {
        delete m_ptr;
    }

    // Copy constructor
	// Do deep copy of a.m_ptr to m_ptr
    Auto_ptr3(const Auto_ptr3& a)
    {
        // Deep copy to prevent double deletion.
        m_ptr = new T;
        *m_ptr = *a.m_ptr; 
    }

    // Copy assignment
	// Do deep copy of a.m_ptr to m_ptr
    Auto_ptr3& operator=(const Auto_ptr3& a)
    {
        if ( &a == this )
            return *this;

        // Release any resource we're holding
        delete m_ptr;

        // Copy the resource
        m_ptr = new T;
        *m_ptr = *a.m_ptr;

        return *this;
    }

    T& operator*() { return *m_ptr; }
    T* operator->() { return m_ptr; }
    bool isNull() const { return m_ptr == nullptr; }
};

template <typename T>
class Auto_ptr4
{
private:
    T* m_ptr{};

public:
    Auto_ptr4(T* ptr=nullptr)
        : m_ptr{ptr}
    {}

    ~Auto_ptr4()
    {
        delete m_ptr;
    }

    // Copy constructor
    Auto_ptr4(const Auto_ptr4& a)
    {
        //Do deep copy of a.m_ptr to m_ptr
        m_ptr = new T;
        *m_ptr = *a.m_ptr;
    }

    // Move constructor
    Auto_ptr4(Auto_ptr4&& a) noexcept
        : m_ptr{a.m_ptr}
    {
        a.m_ptr = nullptr; // set a.m_ptr in a safe state to prevent double deletion
    }

    // Copy assignment
    Auto_ptr4& operator=(const Auto_ptr4& a)
    {
        if ( &a == this )
            return *this;

        delete m_ptr;

        m_ptr = new T;
        *m_ptr = *a.m_ptr; // Do deep copy
    }

    Auto_ptr4& operator=(Auto_ptr4&& a) noexcept
    {
        if ( &a == this )
            return *this;
        
        delete m_ptr;

        m_ptr = a.m_ptr;
        a.m_ptr = nullptr;

        return *this;
    }

    T& operator*() { return *m_ptr; }
    T* operator->() { return m_ptr; }
    bool isNull() const { return m_ptr == nullptr; }
};

// Auto_ptr5 disables copy to prevent unsafe ownership duplication.
// Passing by value (e.g., func(Auto_ptr5<T>)) fails — copy constructor is deleted.
//  Use const ref to read: void func(const Auto_ptr5<T>&);
//  Use r-value ref to move: void func(Auto_ptr5<T>&&); call with std::move(ptr): func(std::move(myPtr));
template <typename T>
class Auto_ptr5
{
private:
    T* m_ptr{};

public:
    Auto_ptr5(T* ptr=nullptr)
        : m_ptr{ptr}
    {}

    ~Auto_ptr5()
    {
        delete m_ptr;
    }

    // Copy constructor deleted
    Auto_ptr5(const Auto_ptr5& a) = delete;

    // Move constructor
    Auto_ptr5(Auto_ptr5&& a) noexcept
        : m_ptr{a.m_ptr}
    {
        a.m_ptr = nullptr; // set a.m_ptr in a safe state to prevent double deletion
    }

    // Copy assignment deleted
    Auto_ptr5& operator=(const Auto_ptr5& a) = delete;

    Auto_ptr5& operator=(Auto_ptr5&& a) noexcept
    {
        if ( &a == this )
            return *this;
        
        delete m_ptr;

        m_ptr = a.m_ptr;
        a.m_ptr = nullptr;

        return *this;
    }

    T& operator*() { return *m_ptr; }
    T* operator->() { return m_ptr; }
    bool isNull() const { return m_ptr == nullptr; }
};

class Resource
{
private:
    static constexpr std::string_view s_str { "This is a static string from static memory." };
public:
    Resource() { std::cout << "Resource acquired.\n"; }
    ~Resource() { std::cout << "Resource destroyed.\n"; }
    void sayHi() const { std::cout << "Hi!\n"; }
    static void print_s_str() { std::cout << s_str << '\n'; }
};

template<typename T>
void printResource(const T& res) // We can read both l-values and r-values without invoking copy or move constructors.
{
    std::cout << "res is " << (res.isNull() ? "null\n" : "not null\n");
}

Auto_ptr4<Resource> generateResource()
{
    Auto_ptr4<Resource> res { new Resource() };
    return res; // the compiler to treat res as an r-value to enable move semantics, so it will invoke the move constructor instead of copying
}

int main()
{
     // An example of crash caused by deleting two equal pointers.
    int* a = new int;
    int* b = a;
    delete a;
    //delete b; // Error: crash because b points to the same memory address as a.
    
    // An example of static members, to recap
    Resource::print_s_str(); 

    // Many acquisitions and destructions of resources - inefficient
    Auto_ptr3<Resource> res { new Resource() };
    Auto_ptr3<Resource> res1 { res }; // res wasn't moved - only copy semantics were used
    Auto_ptr3<Resource> res2;
    res2 = res; // res wasn't moved - only copy semantics were used
    printResource(res); // res wasn't moved - only copy semantics were used
    printResource(res); // res wasn't moved - only copy semantics were used

    // Example of move semantic of Auto_ptr4 - efficient.
    Auto_ptr4<Resource> mainres;
    mainres = generateResource(); // this assignment will invoke the move assignment. generateResource() returns a temporary object (r-value).
    


    return 0;
}
