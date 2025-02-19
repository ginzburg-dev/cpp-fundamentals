#include <iostream>

struct Employee
{
    int id{};
    int age{};
    double wage{};
};

void printEmployee(const Employee& employee)
{
    std::cout << "ID: " << employee.id << '\n';
    std::cout << "AGE: " << employee.age << '\n';
    std::cout << "WAGE: " << employee.wage << '\n';
}

Employee getDefaultEmployee()
{
    return Employee{ 1, 28, 60000.0 };
}

Employee getDefaultEmployee1()
{
    return { 1, 28, 60000.0 };
}

int main()
{   
    printEmployee(Employee{ 1, 34, 55000.0 });
    std::cout << '\n';
    printEmployee({ 2, 32, 50000.0 });
    std::cout << '\n';

    Employee e1 { getDefaultEmployee() };
    printEmployee(e1);

    return 0;
}
