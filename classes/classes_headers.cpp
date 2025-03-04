#include "Point3.h"
#include "Point2.h"
#include <iostream>

class Date
{
private:
    int m_day{};
    int m_month{};
    int m_year{};

public:
    Date(int day, int month, int year); // constructor declaration

    void print() const;

    int getDay() const { return m_day; }
    int getMonth() const { return m_month; }
    int getYear() const { return m_year; }
};

Date::Date(int day, int month, int year) // constructor definition
    : m_day { day }
    , m_month { month }
    , m_year { year }
{
}

void Date::print() const
{
    std::cout << "[" << m_day << ", " << m_month << ", " << m_year << "]\n";
}

int main()
{
    Date date{ 4, 3, 2025 };
    date.print();
    

    Point3 p1 {1.2, 3.4, 5.6}; // from Point3.h
    p1.print(); // from Point3.h

    Point2 p2 { 1.2, 3.4 };
    Point2 p3 { 5.6, 7.8 };

    std::cout << Length(p2, p3) << '\n';

    return 0;
}
