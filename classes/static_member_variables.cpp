#include <iostream>
#include <utility> // for std::pair<T, U>

//  Static members are global variables that live inside the scope region of the class.
class Simple
{
public:
    // Static member var isn't a class object. It exists in static memory so it's just a forward decl and prio to C++17 
    // we need to define it outside the class and make sure that we don't valuate ODR ( define in a linked .cpp for example )
    static int s_value; // declare s_value as static

private:
    static inline int s_idGenerator { 1 }; // a static inline variable can be defined and initialized directly
    int m_id{};

    // auto m_x { 0.5 }; // auto not allowed for non-static members
    // std::pair m_v { 1, 2.3 }; // CTAD not allowed for non-static members
    static inline auto s_x { 5 }; // auto allowed for static-memebers
    static inline std::pair s_v { 1, 2.3 }; // CTAD allowed for static members


public:
    Simple() : m_id { s_idGenerator++ } {}

    int getID() const { return m_id; }
};

int Simple::s_value{ 1 }; // define and initialize s_value to 1.

// Example that can show the difference between extern var and local. 
int g_value; // it's a definition
extern int g_value_extern; // it's just a forward declaration. compiler trust us and doesn't allocate memory immediately. In this case, you can share this var across *.cpp files. Just declare it with forward decl
int g_value_extern{ 1 }; // so we are able to define g_value_extern somewhere in the code e.g. even outside the translation unit

int main()
{
    Simple::s_value = 2;
    std::cout << Simple::s_value << '\n';

    Simple s1{};
    Simple s2{};
    Simple s3{};

    std::cout << s1.getID() << '\n';
    std::cout << s2.getID() << '\n';
    std::cout << s3.getID() << '\n';
    
    return 0;
}
