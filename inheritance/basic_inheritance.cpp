#include <iostream>
#include <string>
#include <string_view>

class Person
{
public:
    std::string m_name{};
    int m_age{};

    Person(std::string_view name="", int age=0)
        : m_name{name}, m_age{age}
    {}

    const std::string& getName() const { return m_name; }
    int getAge() const { return m_age; }
};

// BaseballPlayer class publicly inheriting Person class
class BaseballPlayer : public Person
{
public:
    double m_battingAverage{};
    int m_homeRuns{};

    BaseballPlayer(double battingAverage=0, int homeRuns=0)
        : m_battingAverage{battingAverage}, m_homeRuns{homeRuns}
    {}
};

// Emplayee class publicly inheriting Person class
class Emplayee : public Person
{
public:
    double m_hourlySalary{};
    long m_employeeID{};

    Emplayee(double hourlySalary=0.0, long employeeID=0)
        : m_hourlySalary{hourlySalary}, m_employeeID{employeeID}
    {}

    void print() const
    {
        std::cout << m_name << ": " << m_hourlySalary << '\n';
    }
};

// Supervisor class is derived from Employee class
class Supervisor : public Emplayee
{
public:
    long m_overseesIDs[5]{};
};

int main()
{
    BaseballPlayer joe{};
    joe.m_name = "Joe";
    std::cout << joe.getName() << '\n';

    Emplayee frank{20.25, 12345};
    frank.m_name = "Frank";
    frank.print();

    return 0;
}
