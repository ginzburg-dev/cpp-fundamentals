#include <iostream>

class A
{
public:
    void print() const { std::cout << "A"; }
    virtual void vprint() const { std::cout << "A"; }
};

class B : public A
{
public:
    void print() const { std::cout << "B"; }
    void vprint() const override { std::cout << "B"; }
};

class C
{
private:
    A m_a{};
public:
    virtual A& get() { std::cout << "called C::get()\n"; return m_a; }
};

class D : public C
{
private:
    B m_b{};
public:
    B& get() override { std::cout << "called D::get()\n"; return m_b; }
};

int main()
{
    D d{};
    d.get().print();
    d.get().vprint();

    C c{};
    c.get().print();
    c.get().vprint();

    C& ref{ d };
    ref.get().print();
    ref.get().vprint();

    A* a{ new B };
    a->print(); // prints A
    a->vprint(); // prints B

    return 0;
}
