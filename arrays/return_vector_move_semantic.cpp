#include <iostream>
#include <vector>

std::vector<double> passVector(const std::vector<double>& v1)
{
    std::vector<double> v2{ v1[0] , 2, 3 };
    return v2; // May be moved. Depends on compilator
}

int main()
{
    std::vector v1 { 5.0, 9.9 }; // copy
    std::vector v2 { v1 }; // copy

    std::vector v3 = passVector(v1); // may be move semantic

    return 0;
}
