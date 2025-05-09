#include <iostream>
#include <memory>

// std::shared_ptr is designed for the case where you need multiple smart pointers co-managing the same resource. 
// The resource will be deallocated when the last std::shared_ptr managing the resource is destroyed.

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

int main()
{
    Resource* res{ new Resource() };
    std::shared_ptr<Resource> ptr1{ res };
    {
        std::shared_ptr<Resource> ptr2 { ptr1 }; // Important: always make a copy of an existing std::shared_ptr if you need more than one std::shared_ptr pointing to the same resource.
        std::cout << "Killing ptr2 shared pointer\n";
    }

    std::cout << "Killing ptr1 shared pointer\n";

    // Example: std::make_shared<>()

    auto ptr3{ std::make_shared<Resource>() };
    {
        auto ptr4{ ptr3 }; // create ptr3 using copy of ptr2
        std::cout << "Killing ptr4 shared pointer\n";
    }
    std::cout << "Killing ptr3 shared pointer\n";

    // Example: Shared pointers can be created from unique pointers, but not the other way around.

    auto uniquePtr{ std::make_unique<Resource>(1, 2) };
    std::shared_ptr<Resource> sharedPtr{ std::move(uniquePtr) }; // convert to a shared pointer

    auto sharedPtr1{ std::make_shared<Resource>(1, 2) };
    //std::unique_ptr<Resource> uniquePtr1{ std::move(sharedPtr1) }; // Error: we're not able to convert shared_ptr to unique_ptr (ownership is shared, not exclusive)
    
    // Example: shared_ptr and arrays
    std::shared_ptr<Resource[]> sharedPtr_array(new Resource[4], [](Resource* p){ delete[] p; }); // in C++20, std::shared_ptr does have support for arrays. In C++11 - 17 we need to use custom deleter

    // Example: std::shared_ptr supports copy — ownership is shared. Discarded resource is destroyed if no other shared_ptr owns it.
    auto tmp1{ std::make_shared<Resource>(1, 2) };
    auto tmp2{ std::make_shared<Resource>(3, 4) };

    tmp2 = tmp1; // tmp2 and tmp1 now share the same resource

    return 0;
}
