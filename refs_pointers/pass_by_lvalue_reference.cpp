#include <iostream>

// no copy of a vriable passed as an argument needs to be made
void printValue(std::string& s)
{
    std::cout << s << '\n';
}

void printAdresses(int val, int& ref)
{
    std::cout << "The address of the value parameter is: " << &val << '\n';
    std::cout << "The address of the reference parameter is: " << &ref << '\n';
    ++ref; // this modifies the actual object
}

int main()
{
    std::string s { "Hello!" };
    const std::string cs { "Const string" }; 
    printValue(s);
    //printValue( "World!" ); // error: "World!" is an rvalue
    //printValue( cs ); // error: cs is a non-modifiable lvalue

    // The above example demonstrates that a value parameter is a separate object from the argument
    int x { 5 };
    std::cout << "the value of x is: " << x << '\n';
    std::cout << "the address of x is: " << &x << '\n';
    printAdresses(x,x);
    std::cout << "the value of x is: " << x << '\n';

    return 0;
}
