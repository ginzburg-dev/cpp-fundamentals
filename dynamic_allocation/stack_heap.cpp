#include <iostream>

void recursion()
{
    static int count{1};
    
    int x[10]{};

    recursion(); // call itself

    std::cout << count++ << '\n';
}

int main()
{
    int stack[10000000]{};
    std::cout << stack[0] << '\n'; // this can cause run out of stack memory
    
    recursion(); // it's also cause the stack overflow

    return 0;
}
