#include <iostream>
#include <algorithm>
#include <array>
#include <functional>
#include <string_view>

/*
When passing a lambda to a function:
- If C++20 capable, use auto as the parameter’s type.
- Otherwise, use a function with a type template parameter or std::function parameter (or a function pointer if the lambda has no captures).
*/

void repeat1(int n, std::function<void(int)> fn)
{
    std::cout << "Repeat 1" << '\n';
    for (int i{0}; i < n; ++i)
        fn(i);
}

template <typename T>
void repeat2(int n, const T& fn)
{
    std::cout << "Repeat 2" << '\n';
    for (int i{0}; i < n; ++i)
        fn(i);
}

// Case 3: use the abbreviated function template syntax (C++20)
void repeat3(int n, const auto& fn)
{
    std::cout << "Repeat 3" << '\n';
    for (int i{0}; i < n; ++i)
        fn(i);
}

// Case 4: use function pointer (only for lambda with no captures)
void repeat4(int n, void (*fn)(int))
{
    std::cout << "Repeat 4" << '\n';
    for (int i{0}; i < n; ++i)
        fn(i);
}

// Behind-the-scenes structure of a lambda
struct GenericLambda
{
    template <typename T>
    void operator()(T x) const { 
        return x * 2; 
    }
};

int main()
{
    // Example 1

    // A word of advice. When storing a lambda in a variable, use auto as the variable’s type.

    // A regular function pointer. Only works with an empty capture clause (empty [])
    double (*addNumbers1)(double, double) { [](double a, double b){ return a + b; } }; 
    std::cout << "func addNumber1: " << addNumbers1(1.2, 3.4) << '\n';

    // using std::function. The lambda could have a non-empty capture clause.
    std::function<double(double,double)> addNumbers2 { [](double a, double b){ return a + b; } }; // note: pre-C++17, use std::function<double(double, double)> instead
    std::cout << "func addNumber2: " << addNumbers2(5.6, 7.8) << '\n';

    // Prefer using auto. Stores Lambda with its real type. 
    auto addNumbers3 { [](double a, double b){ return a + b; } };
    std::cout << "func addNumber3: " << addNumbers3(9.1, 2.3) << '\n';

    // Example 2

    auto lambda = [](int i)
    {
        std::cout << i << '\n';
    };

    lambda(100); // call lambda

    repeat1(3, lambda);
    repeat2(3, lambda);
    repeat3(3, lambda);
    repeat4(3, lambda);

    std::cout << '\n';

    // Example 3. Algorithm. std::adjacent_find

    constexpr std::array months{ // pre-C++17 use std::array<const char*, 12>
        "January",
        "February",
        "March",
        "April",
        "May",
        "June",
        "July",
        "August",
        "September",
        "October",
        "November",
        "December"
    };

    const auto sameLetter { std::adjacent_find(months.begin(), months.end(),
        [](const auto& a, const auto& b){
            return a[0] == b[0];
    }) };

    if ( sameLetter != months.end() )
    {
        std::cout << *sameLetter << " and " << *std::next(sameLetter) << " start with the same letter.\n";
    }

    // Example 4. Algorithm std::all_of

    constexpr std::array<int, 5> arr1 { 2, 4, 6, 8, 12 };
    constexpr std::array<int, 6> arr2 { 2, 4, 6, 8, 12, 15 };
    bool ifOdd1 { std::all_of(arr1.begin(), arr1.end(), [](int i){ return ( i % 2 == 0 ); } ) };
    bool ifOdd2 { std::all_of(arr2.begin(), arr2.end(), [](int i){ return ( i % 2 == 0 ); } ) };
    std::cout << "\nExample 4 ifOdd1: " << ifOdd1 << '\n'; 
    std::cout << "Example 4 ifOdd2: " << ifOdd2 << '\n'; 

    // Example 5. Algorithm std::find_if

    constexpr std::array<std::string_view, 3> arr3 { "milk", "juse", "water" };
    const auto found { std::find_if(arr3.begin(),arr3.end(), [](std::string_view str){ return str.find("mil") != std::string_view::npos; } ) };
    if ( found != arr3.end() )
        std::cout << "\nExample 5 found: " << *found << '\n';
    else
        std::cout << "\nExample 5 not found.\n";

    // Example 6. Algorithm std::count_if 

    constexpr std::array<std::string_view, 5> arr4 { "cow", "rat", "bug", "heard", "frog" };

    // Count how many words consists of 3 letters
    auto count { std::count_if(arr4.begin(), arr4.end(), 
        [](std::string_view str){ 
            return str.length() == 3; 
    }) };
    
    std::cout << "Example 5 count: " << count << '\n';

    // Example 7 Static

    // Every call to a generic lambda (templated via auto) with a different value type initializes a unique static callCaount variable
    auto print{
        [](auto value){
            static int callCount{1};
            std::cout << callCount++ << ": " << value << '\n';
        }
    };

    print(1); // 1: 1
    print(2); // 2: 2

    print(3.4); // 1: 3.4

    print("Hello"); // 1: Hello
    print("Static"); // 2: Static

    // Example 8 Lambda's return type

    []()->double{};
    auto divide { [](int x, int y, bool intDivision) -> double {
        if ( intDivision )
            return x / y;
        else
            return static_cast<double>(x) / y;
    }};
    
    std::cout << divide(3, 2, true) << '\n';
    std::cout << divide(3, 2, false) << '\n';

    // Example 9 Standard library function objects

    // std::greater in <functional> header
    std::array arr5 { 100, 50, 22, 79, 3, 949, 2 };

    std::sort(arr5.begin(), arr5.end(), std::greater{}); // note: need cusly braces to instantiate object

    for ( int i : arr5 )
        std::cout << i << ' ';
    
    return 0;
}
