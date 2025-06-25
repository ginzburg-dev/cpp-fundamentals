#include <iostream>
#include <string>
#include <string_view>

class Base
{
public:
    friend std::ostream& operator<<(std::ostream& out, const Base& b)
    {
        return b.print(out);
    }

    virtual std::ostream& print(std::ostream& out) const
    {
        out << "Base";
        return out;
    }
};

struct Employee
{
    std::string m_name{};
    int id{};

    friend std::ostream& operator<<(std::ostream& out, const Employee& e)
    {
        out << "Employee(\"" << e.m_name << "\", " << e.id << ")";
        return out;
    }
};

class Derived : public Base
{
private:
    Employee m_employee{};

public:
    Derived(const Employee& e)
        : m_employee{ e }
    {}
    std::ostream& print(std::ostream& out) const override
    {
        out << m_employee;
        return out;
    }
};

int main()
{
    Base b{};
    std::cout << b << '\n';

    Derived d{ Employee{"Jim", 1} };
    std::cout << d << '\n';

    Base& bref{ d };
    std::cout << bref << '\n';

    return 0;
}
