#include <iostream>

struct Employee
{
    int id {};
    int age {};
    double wage {};
};

int main()
{
    Employee joe { 14, 32, 60000.0 };

    Employee frank {};
    frank.id = 15;
    frank.age = 28;
    frank.wage = 45000.0;

    int totalAge { joe.age + frank.age };
    std::cout << "Joe and Frank have lived " << totalAge << " total years\n";

    if (joe.wage > frank.wage)
        std::cout << "Joe makes more than Frank\n";
    else if (joe.wage > frank.wage)
        std::cout << "Frank makes more than Joe\n";
    else
        std::cout << "Joe and Frank make the same amount\n";

    // frank got a promotion
    frank.wage += 5000.0;

    // Today is Joe's birthday
    ++joe.age;
    
    return 0;
}
