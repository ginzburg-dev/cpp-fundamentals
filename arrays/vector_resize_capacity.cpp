#include <vector>
#include <iostream>

int main()
{
    std::vector<int> v1 { 0, 1, 2 };
    v1.resize(5);

    for (auto i : v1)
        std::cout << i << ' ';
    std::cout << '\n';
    
    std::cout << "Capacity: " << v1.capacity() << " Length: " << v1.size() << '\n'; // Capacity: 6 Length: 5

    v1.resize(3); // shrinking to 3 doesn't do reallocation, only the lenght can be changed, not the capacity

    std::cout << "Capacity: " << v1.capacity() << " Length: " << v1.size() << '\n'; // Capacity: 6 Length: 3.
    
    v1[3] = 10; // subscript [] is only valid if it is between 0 and the vector's length (not it's capacity)

    v1.shrink_to_fit(); // // Capacity: 3 Length: 3. Shrink the capacity to lenght
    
    return 0;
}
