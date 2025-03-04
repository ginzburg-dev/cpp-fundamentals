#include <iostream>

class Simple
{
private:
    int m_id{};

public:
    Simple(int id = 0)
        : m_id { id }
    {
    }

    int getID() const { return m_id; }
    void setID(int id) { this->m_id = id; }
    // static void setID(Simple* const this, int id) { this->m_id = id; } - the compiler rewrites our setID() functions like this
    Simple& increase() { ++m_id; return *this; } // increase m_id and return ref of *this. Thus we can chain member funcs together
    Simple& plus(int value) { m_id += value; return *this; } // can be chaining
    void print() const { std::cout << this->m_id << '\n'; } // use `this` pointer to access the implicit object and operator-> to select member m_id

    void reset()
    {
        *this = {}; // it creates default-initialized Simple object then copy-assigned to *this. reset all members to their default
    }
};

int main()
{
    Simple simple{1};
    simple.setID(4);

    simple.print();

    simple.increase().plus(10).print(); // an example of chaining memeber function calls together

    simple.reset(); // reset. *this = {};

    return 0;
}
