#include <iostream>
#include <memory> // for std::unique_ptr

// Favor std::array, std::vector, or std::string over a smart pointer managing a fixed array, dynamic array, or C-style string.

class Resource
{
private:
    int m_first{};
    int m_second{};

public:
    Resource(int first=0, int second=0)
        : m_first{first}, m_second{second}
    {
        std::cout << "Resource acquired\n";
    }

    ~Resource()
    {
        std::cout << "Resource destroyed\n";
    }

    int getFirst() const { return m_first; }
    int getSecond() const { return m_second; }
};

std::ostream& operator<<(std::ostream& out, const Resource&) // invokes if we pass Resouerce object
{
    out << "I am a Resource";
    return out;
}

// Why is it better to use std::make_unique<>()?
// Let's take a look at this function call:
// some_function(std::unique_ptr<T>(new T), function_that_can_throw_exception());
// Prior to C++17, there is no guaranteed order of evaluation for function arguments,
// so this can lead to issues with memory allocation.
// If function_that_can_throw_exception() throws an exception,
// the dynamically allocated memory may not be properly deleted.

std::unique_ptr<Resource> createResource()
{
    return std::make_unique<Resource>();
}

void takeOwnership(std::unique_ptr<Resource> res)
{
    std::cout << "takeOwnership() called\n";
    if (res)
        std::cout << *res << '\n';
}


// The function only uses the resource, so we'll accept a pointer to the resource, not a reference to the whole std::unique_ptr<Resource>
void useResource(const Resource* res) 
{
    std::cout << "useResource() called\n";
    if (res)
        std::cout << *res << '\n';
}

int main()
{
    std::unique_ptr<Resource> res{ new Resource{} };
    std::unique_ptr<Resource> res1{};

    if (res) // std::unique_ptr has bool cast that return 'true' if object is valid
        std::cout << "res : " << *res << '\n'; // print the Resource that res is owning

    std::cout << "res is " << ( res ? "not null" : "null" ) << '\n';
    std::cout << "res1 is " << ( res1 ? "not null" : "null" ) << '\n';

    res1 = std::move(res); // in std::unique_ptr copy initialization and copy assignment are disabled

    std::cout << "res is " << ( res ? "not null" : "null" ) << '\n';
    std::cout << "res1 is " << ( res1 ? "not null" : "null" ) << '\n';

    // Example: std::make_unique

    auto res2 { std::make_unique<Resource>(1, 2) };
    std::cout << *res2 << '\n';

    // Create a dynamically allocated array of Resource of length 4
    auto res3 { std::make_unique<Resource[]>(4) };
    std::cout << res3[0] << '\n';

    // Use std::make_unique() instead of creating std::unique_ptr and using new yourself.

    // Example: Returning std::unique_ptr from a function

    auto res4{ createResource() }; // in C++ 17 and newer, this return will be elided. Prior C++17 it invokes move semantics


    // Example: Passing std::unique_ptr to a function

    auto res5{ std::make_unique<Resource> (1, 2) };
    //takeOwnership(res5); // This doesn't work, need to use move semantics
    takeOwnership(std::move(res5)); // ok: use move semantics
    std::cout << "Move std::unique_ptr to a function. Res5 is " << ( res5 ? "not null" : "null" ) << '\n';

    auto res6{ std::make_unique<Resource> (1, 2) };
    useResource(res6.get()); // Uses a Resource without moving it. note: get() used here to get a pointer to the Resource.
    std::cout << "Just passing std::unique_ptr to a function. Res6 is " << ( res6 ? "not null" : "null" ) << '\n';

    return 0;
}
