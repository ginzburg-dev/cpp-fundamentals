#include <iostream>

class Emplayee
{
    int m_id {};
    int m_age {};
    double m_wage {};
};

class Date
{
public:
    int m_day {};
    int m_month {};
    int m_year {};
};

void printDate(const Date& date)
{
    std::cout << date.m_day << '/' << date.m_month << '/' << date.m_year << '\n';
}

int main()
{
    Date date { 25, 02, 2024 };
    printDate(date);

    return 0;
}
