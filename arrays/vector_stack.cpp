#include <iostream>
#include <vector>

// Favor constexpr std::bitset, std::vector<char>, or 3rd party dynamic bitsets over std::vector<bool>.

class Foo
{
private:
    std::string m_a{};
    int m_b{};

public:
    Foo(std::string_view a, int b)
        : m_a { a }
        , m_b { b }
    {}

    explicit Foo(int b)
        : m_a {}, m_b { b }
    {}
};

void printStack(const std::vector<int>& stack)
{
    if ( stack.empty() )
        std::cout << "Empty";
    
    for ( auto i : stack )
        std::cout << i << ' ';

    std::cout << "\tCapacity: " << stack.capacity() << " Length: " << stack.size() << '\n';
}

int main()
{
    std::vector<int> stack{};
    printStack(stack); // Empty	Capacity: 0 Length: 0

    stack.reserve(6);  // Allocate 6 elements without changing the length
    printStack(stack); // Empty	Capacity: 6 Length: 0

    stack.push_back(1);
    printStack(stack);

    stack.push_back(2);
    printStack(stack); // Capacity: 2 Length: 2

    stack.push_back(3);
    printStack(stack); // Capacity: 4 Length: 3 . It's an extra capacity. A multiplicator of the capacity depends on compiller

    std::cout << "Top: " << stack.back() << '\n'; // top element

    stack.pop_back();
    printStack(stack); // Capacity: 4 Length: 2

    stack.pop_back();
    printStack(stack); // Capacity: 4 Length: 1

    stack.pop_back();
    printStack(stack); // Empty, Capacity: 4 Length: 0

    
    std::vector<Foo> stack1{};

    Foo f{ "a", 2 };

    stack1.push_back(f); // prefer this one
    stack1.emplace_back(f); // also ok

    stack1.push_back( {"a", 2} ); // push temporary object
    stack1.emplace_back("a", 2); // OK, preferable. It can invoke constructors (explicit as well)

    //stack1.push_back( { 2 } ); // compile error: Foo(int) is explicit. push_back won't use explicit constructors
    stack1.emplace_back( 2 ); // OK, emplace_back can use explicit constructors

    return 0;
}
