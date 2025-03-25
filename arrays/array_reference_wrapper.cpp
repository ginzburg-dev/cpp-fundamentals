#include <iostream>
#include <array>
#include <functional> // for std::reference_wrapper

// std::reference_wrapper can be used in arrays that contain with references

int main()
{
    int x { 5 };
    std::reference_wrapper<int> ref1 { x };
    std::reference_wrapper ref2 { x }; // C++17
    auto ref2_adv { std::reference_wrapper{ x } };

    auto ref3 { std::ref(x) }; // C++11, deduced to std::reference_wrapper<int>
    auto cref3 { std::cref(x) }; // C++11, deduced to std::reference_wrapper<const int>

    std::array<std::reference_wrapper<int>, 1> arr1 { x };
    arr1[0].get() = 5; // modify the object in array element 0
    std::cout << arr1[0] << '\n';

    return 0;
}
