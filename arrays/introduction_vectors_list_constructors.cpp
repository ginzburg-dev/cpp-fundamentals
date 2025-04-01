#include <iostream>
#include <vector>

class V
{
public:
    std::vector<int> m_data { std::vector<int>(8) }; // direct default initialization isn't allowed for class members
};

int main()
{
    std::vector<int> numbers { 1, 2, 3, 4, 5 };
    std::vector chars { 'a', 'b', 'c', 'd' }; // uses CTAD (C++17) to deduce element type (preferred)

    std::cout << sizeof(int) << '\n';
    std::cout << (&numbers[0]) << '\n';
    std::cout << (&numbers[1]) << '\n';
    std::cout << (&numbers[2]) << '\n';

    std::vector<int> data(10); // vector containing 10 elements. It must be constructed using direct initialization
    
    const std::vector constVec { 1, 2, 3, 4 }; // const-ness of the vector
    
    std::cout << "Enter 3 integers: ";
    std::vector<int> arr(3);
    std::cin >> arr[0] >> arr[1] >> arr[2];
    std::cout << "The sum is " <<arr[0] + arr[1] + arr[2] << '\n';
    std::cout << "The product is " <<arr[0] * arr[1] * arr[2] << '\n';
    
    return 0;
}
