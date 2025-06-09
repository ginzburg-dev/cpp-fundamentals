#include <iostream>
#include <string>
#include <string_view>
#include <vector>
#include <functional>

// Although C++ supports assigning derived objects to base objects via object slicing, in general, 
// this is likely to cause nothing but headaches, and you should generally try to avoid slicing. 
// Make sure your function parameters are references (or pointers) and try to avoid any kind of pass-by-value 
// when it comes to derived classes.

class Base
{
private:
    int m_value{};

public:
    Base(int value)
        : m_value{value}
    {}

    //Base(const Base& base) = delete;
    //Base& operator=(const Base& base) = delete;

    virtual ~Base() = default;

    virtual std::string_view getName() const { return "Base"; }
    int getValue() const { return m_value; }
};

class Derived : public Base
{
public:
    Derived(int value)
        : Base{value}
    {}

    std::string_view getName() const override { return "Derived"; }
};

void slicingFunction(const Base base)
{
    std::cout << "I'm a " << base.getName() << " and has value " << base.getValue() << '\n';
}

int main()
{
    Derived derived{5};
    Base base{ derived }; // Derived portion has effectively been “sliced off”
    std::cout << "base is a " << base.getName() << " and has value " << base.getValue() << '\n'; // Prints: base is a Base and has value 5
    
    // function slicing
    slicingFunction(derived); // Sliced off a derived part. Prints: I'm a Base and has value 5

    // vector slicing
    std::vector<Base> v{};
    v.push_back(Base{5});
    v.push_back(Derived{6});

    for (const auto& element : v)
        std::cout << "I am a " << element.getName() << " with value " << element.getValue() << '\n';
    // This prints:
    // I am a Base with value 5
    // I am a Base with value 6

    // assignment slicing
    Derived d1{1};
    Derived d2{2};
    Base& b{ d1 };
    b = d2; // only the Base portion of d2 is copied into d1
    // slicing can be avoided by making the Base class non-copyable 
    // (by deleting the Base copy constructor and Base assignment operator).

    return 0;
}
