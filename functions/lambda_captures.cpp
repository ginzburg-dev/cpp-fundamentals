#include <iostream>
#include <algorithm>
#include <array>
#include <vector>
#include <functional> // includes std::reference_wrapper and std::ref

int g_global{ 10 };

struct Enemy
{
    int helth{};
    std::string_view name{};
};

void myInvoke(const std::function<void()>& fn)
{
    fn();
}

int main()
{
    // Example 1. The scope of visibility for variables that don't need to be captured
    constexpr int x{ 20 };
    const int y{ 25 };
    static int s_int{ 30 };

    // No capture needed because global, static, and constexpr variables are visible to the lambda
    auto lambda{ [](){ 
        std::cout << x << ' ' << y << ' ' << g_global << ' ' << s_int << '\n';
    } };

    lambda();
    
    // Example 2. Mutable. How to modify copy of captured variable

    int mutableX { 10 };

    [x](){}; // x is const in that case

    auto lambda1 { [mutableX]() mutable { // 'mutable' keyword allows us to modify copies of captured variables across multiple lambda calls, without changing the original variables
        ++mutableX;
        std::cout << mutableX << '\n';
    } };

    lambda1();

    std::cout << mutableX << '\n';

    // Example 3. Capture reference to modify the original variable

    int ammo{ 1 };
    auto lambda2 { [&ammo](){
        ++ammo;
    } };

    lambda2();

    std::cout << "Ammo: " << ammo << '\n';

    // Example 4. Capture reference. sort.

    std::array arr { 92, 5, 20, 50, 3, 55 };
    
    int comparisons{0};
    std::sort(arr.begin(), arr.end(), [&comparisons](const auto& a, const auto& b){
        ++comparisons;
        return a < b;
    });

    std::cout << "Comparisons: " << comparisons << '\n';
    for ( auto i : arr )
        std::cout << i << ' ';
    std::cout << '\n';

    // Example 5. Multiple captures

    [x, &arr](){};

    // Example 6. Default capture

    int health{ 100 };
    int armor{ 50 };
    std::vector<Enemy> enemies{};

    [=](){}; // Capture all variables used inside the lambda by value
    [&](){}; // Capture all variables used inside the lambda by reference

    [=, &enemies](){}; // enemies captures by reference, but other variables by value
    [&, health](){}; // Capture 'health' by value, and all other variables by reference

    // Example 7. Defining a new variable in the lambda-capture

    auto lambda3 = [newVariable{ x + 10 }](){ 
        /*newVariable is only visible inside the lambda*/ 
        std::cout << newVariable << '\n';
    };

    lambda3();

    // Example 7. Unintended copies of mutable lambdas

    int i { 0 };
    auto lambda4 = [i]()mutable{
        std::cout << i++ << '\n';
    }; 

    myInvoke(lambda4); // converts the lambda to std::function and creates a copy
    myInvoke(lambda4);
    myInvoke(lambda4);
    /*Output: 0 0 0 */

    // Fixed veraion 1. use std::function
    std::function lambda4_func = [i]()mutable{
        std::cout << i++ << '\n';
    };
    myInvoke(lambda4_func);
    myInvoke(lambda4_func);
    myInvoke(lambda4_func);
    /*Output: 0 1 2 */

    // Fixes version 2. use std::ref
    myInvoke(std::ref(lambda4)); // std::reference_wrapper prevents copying the lambda or function object
    myInvoke(std::ref(lambda4));
    myInvoke(std::ref(lambda4));
    /*Output: 0 1 2 */

    return 0;
}
