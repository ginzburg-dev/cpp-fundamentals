#include <functional>
#include <iostream>

int getInteger()
{
    std::cout << "Enter an integer: ";
    int value{};
    std::cin >> value;

    return value;
}

char getOperator()
{
    char op{};

    do
    {
        std::cout << "Enter an operator: ";
        std::cin >> op;
    }
    while ( op != '+' && op != '-' && op != '*' && op != '/'  );

    return op;
}

int add(int x, int y)
{
    return x + y;
}

int substract(int x, int y)
{
    return x - y;
}

int multiply(int x, int y)
{
    return x * y;
}

int divide(int x, int y)
{
    return x / y;
}

using ArithmeticFunction = std::function<int(int, int)>;

ArithmeticFunction getArithmeticFunction(char op)
{
    switch (op)
    {
    case '+': return &add;
    case '-': return &substract;
    case '*': return &multiply;
    case '/': return &divide;
    }

    return nullptr;
}

int main()
{
    int x { getInteger() };
    char op { getOperator() };
    int y { getInteger() };

    auto aFunc { getArithmeticFunction(op) };
    if (aFunc)
        std::cout << x << ' ' << op << ' ' << y << " = " << aFunc(x,y) << '\n';

    return 0;
}
