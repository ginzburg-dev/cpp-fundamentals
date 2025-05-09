#include <iostream>
#include <string>
#include <memory>

// shared_ptr = shared ownership (keeps object alive); weak_ptr = non-owning observer (avoids cycles, use lock() to access).
// unique_ptr = sole owner, movable; shared_ptr = shared ownership, ref-counted; weak_ptr = non-owning observer, use lock() to access.
// weak_ptr can't exist alone — it needs a shared_ptr to keep the object alive.

// std::shared_ptr can be used when you need multiple smart pointers that can co-own a resource. 
// The resource will be deallocated when the last std::shared_ptr goes out of scope. 
// std::weak_ptr can be used when you want a smart pointer that can see and use a shared resource, 
// but does not participate in the ownership of that resource.

class Person
{
private:
    std::string m_name{};
    std::weak_ptr<Person> m_partner{};

public:
    Person(const std::string& name)
        : m_name{name}
    {
        std::cout << m_name << " created.\n";
    }

    ~Person()
    {
        std::cout << m_name << " destroyed.\n";
    }

    friend bool partnerUp(std::shared_ptr<Person>& p1, std::shared_ptr<Person>& p2)
    {
        if ( !p1 || !p2 )
            return false;
        
        p1->m_partner = p2;
        p2->m_partner = p1;

        std::cout << p1->m_name << " now is partnered with " << p2->m_name << '\n';

        return true;
    }

    std::shared_ptr<Person> getPartner() const { return m_partner.lock(); } // use lock() to convert weak_ptr to shared_ptr
    const std::string& getName() const { return m_name; }
};

Person* getDumbPtr()
{
    auto ptr{ std::make_unique<Person>("Noname") };
    return ptr.get();
} // ptr goes out of scope, Person destroyed

std::weak_ptr<Person> getWeakPtr()
{
    auto ptr{ std::make_shared<Person>("Noname") };
    return std::weak_ptr<Person>{ ptr };
} // ptr goes out of scope, Person destroyed

int main()
{
    auto dim { std::make_shared<Person>("Dim") };
    auto linda { std::make_shared<Person>("Linda") };

    partnerUp(dim, linda);

    auto partner = dim->getPartner(); // get shared_ptr to Dim's partner. It gives us a temporary shared_ptr so this is safe and does not introduce a circular dependency
    std::cout << dim->getName() << "'s partner is " << partner->getName() << '\n';

    // Example: Avoiding dangling pointers with std::weak_ptr

    auto dumb{ getDumbPtr() };
    std::cout << "Dumb ptr is " << ( (dumb == nullptr) ? "null" : "not null" ) << '\n';

    auto weak{ getWeakPtr() };
    std::cout << "Weak ptr is " << ( weak.expired() ? "null" : "not null" ) << '\n'; // .expired() member function to validate std::weak_ptr

    return 0;
}
