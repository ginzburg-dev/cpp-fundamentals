#include <iostream>

int main()
{
    // pointer to const
    const int x { 5 };
    const int* ptr { &x };

    const int y { 6 };
    ptr = &y;

    int x1{ 1 };
    const int* ptr1 { &x1 };
    //*ptr1 = 7; // not allowes so it's a const pointer and we can't change value through ptr1
    x1 = 7;

    // const pointer
    int x2 { 2 };
    int y2 { 5 };
    int* const ptr2 { &x1 };
    //ptr2 = &y2; // error: once initialized, a const pointer can not be changed.
    *ptr2 = 2; // okay: the value being pointed to is non-const

    int x3 { 7 };
    const int* const ptr3 { &x2 }; // a const pointer to a const value


    return 0;
}
