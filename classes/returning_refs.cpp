#include <iostream>
#include <string>
#include <string_view>

class Employee
{
private:
    int m_id{};
    std::string m_name{};

public:
    void setName(std::string_view name) { m_name = name; }
    const std::string& getName() const { return m_name; }
    const auto& getNameDeduce() const { return m_name; } // auto obscures the return type. Prefer explicit return types
    int& getID() { return m_id; } // returns a non-const reference (don't do this)
};

int main()
{
    Employee joe{};
    joe.setName("Joe");

    std::cout << joe.getName();

    joe.getID() = 5; // now we have an access to private member. This allows the caller to subvert the access control system
    std::cout << joe.getID() << '\n';

    return 0;
}
