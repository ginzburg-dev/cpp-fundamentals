#include <iostream>
#include <typeinfo>

int main()
{
    int x { 5 };
    int& ref { x };
    std::cout << &x << '\n'; // print the memory address of variable x
    
    int* ptr0; // a wild pointer that contain a garbage address
    int* ptr3, * ptr4;

    int y { 6 };
    int* ptr { &x };
    std::cout << *ptr << '\n';

    ptr = &y;
    std::cout << *ptr << '\n';

    *ptr = 7; // modify the value of the object at the address held by ptr
    std::cout << *ptr << '\n';

    std::cout << typeid(x).name() << '\n'; // print the type of x ( int )
    std::cout << typeid(&x).name() << '\n'; // The address-of operator returns a pointer ( int* )
    std::cout << sizeof(&x) << '\n'; // size of pointer on a 64-bit machine is 64 bits ( 8 bytes )

    return 0;
}
