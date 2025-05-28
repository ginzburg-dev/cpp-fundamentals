#include <iostream>

class Base
{
private:
    int m_value{};

public:
    Base(int value)
        : m_value{value}
    {}

    int getValue() const { return m_value; }
    void deletedFunc() const { std::cout << "deleted\n"; }

protected:
    void print() const { std::cout << m_value << '\n'; }
};

class Derived : public Base
{
private:
    using Base::getValue; // make ALL getValue functions private

public:
    Derived(int value)
        : Base{value}
    {}

    // Base::print was inherited as protected, so the public has no access
    // But we're changing it to public via a using declaration
    using Base::print; // note: no parenthesis here

    void deletedFunc() const = delete; // mark this function as inaccessible in a Derived class
};

int main()
{
    Derived derived{2};
    derived.print();

    derived.Base::deletedFunc(); // We can access Base::deletedFunc() directly
    static_cast<Base&>(derived).deletedFunc(); // Or leverage static_cast

    return 0;
}
