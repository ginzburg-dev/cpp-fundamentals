#include <iostream>
#include <string>

template<typename T>
void print(const T& p)
{
    std::cout << p << '\n';
}

// Specialization by defining a non-template function has the highest precedence
void print(int p) // not implicitly 'inline'
{
    std::cout << "Max precedence (int) specialization: " << p << '\n';
}

template<>
void print<double>(const double& p) // not implicitly 'inline'
{
    std::cout << "Scientific specialization: " << std::scientific << p << '\n';
}

template<>
void print<std::string>(const std::string& p) = delete; // not implicitly 'inline'

int main()
{
    print(2); // Prints: Max precedence (int) specialization: 2
    print(2.7447469); // Prints: Scientific specialization: 2.744747e+00
    // print(std::string("C-String")); // Error: call to deleted function print

    return 0;
}
