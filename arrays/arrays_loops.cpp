#include <iostream>
#include <vector>

template <typename T>
T calculateAverage(const std::vector<T>& arr)
{
    std::size_t length { arr.size() };

    T average { 0 };
    for (std::size_t index { 0 }; index < length; ++index)
        average += arr[index];
    average /= static_cast<int>(length);

    return average;
}

int main()
{
    std::vector testScore1 { 50, 21, 54, 32, 22, 11, 67, 83, 55, 23, 41, 49 };
    std::cout << "The average score is " << calculateAverage(testScore1) << '\n'; // calc int

    std::vector testScore2 { 56.43, 67.22, 87.3 };
    std::cout << "The average score is " << calculateAverage(testScore2) << '\n'; // calc doubles

    return 0;
}
