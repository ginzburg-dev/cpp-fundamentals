#include <iostream>

int main()
{
    int x{ 10 };
    char word[]{ "Word" };
    double d{ 6.7 };

    void* x_ptr{ &x }; // void* pointer can point to any type of object 
    void* word_ptr{ &word };
    void* d_ptr{ &d };

    std::cout << "int* :" << *static_cast<int*>(x_ptr) << '\n'; // void* must be cast to another pointer type before dereferencing
    std::cout << "char* :" << static_cast<char*>(word_ptr) << '\n';
    std::cout << "double* :" << *static_cast<double*>(d_ptr) << '\n';

    return 0;
}
