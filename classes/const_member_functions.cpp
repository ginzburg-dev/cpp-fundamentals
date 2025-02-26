#include <iostream>

// A member function that does not (and will not ever) modify the state of the object should be made const, 
//so that it can be called on both const and non-const objects.

void nonConstFunc()
{

}

struct Date
{
    int day {};
    int month {};
    int year {};

    void nonConstFunc()
    {

    }

    void constFunc() const
    {

    }

    void print() const
    {
        std::cout << '[' << day << '/' << month << '/' << year << "]\n";
        //Date::nonConstFunc(); // error: called member function must be const in this case
        ::nonConstFunc(); // calling a non-const non-member function from the global scope is allowed
        constFunc(); // calling const function is allowed here
    }

    void printNonConst()
    {
        std::cout << '[' << day << '/' << month << '/' << year << "]\n";
    }

    void someFuncOverload()
    {
        std::cout << "non-const func is called\n";
    }

    void someFuncOverload() const
    {
        std::cout << "const func is called\n";
    }
};

void doSomething(const Date& date)
{
    //date.printNonConst(); // error: since we can't call non-const memeber func on const object (we're passing through const ref)
    date.print(); // ok, it works, so that the print() is a const memeber func
}

void doSomethingConst(const Date& date)
{
    date.print();
}

int main()
{
    const Date today { 26, 02, 2025 };

    today.print();

    Date nonConstDate { 27, 02, 2025 };
    doSomething(nonConstDate); 

    Date nonConstOverload { 28, 02, 2025 };
    const Date constOverload { 29, 02, 2025 };

    nonConstOverload.someFuncOverload(); // calls someFuncOverload()
    constOverload.someFuncOverload(); // calls someFuncOverload() const

    return 0;
}
