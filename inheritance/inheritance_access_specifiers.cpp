#include <iostream>

// It’s better to make your members private if you can, 
// and only use protected when derived classes are planned and the cost to 
// build and maintain an interface to those private members is too high.

// Making your members private means the public and derived classes can’t directly make changes to the base class. 
// This is good for insulating the public or derived classes from implementation changes, 
// and for ensuring invariants are maintained properly. 
// However, it also means your class may need a larger public (or protected) interface to support 
// all of the functions that the public or derived classes need for operation, which has its own cost to 
// build, test, and maintain.

class Base
{
private:
    int m_private{}; // can be accessed by Base mambers, friends (but not derived classes)
protected:
    int m_protected{}; // can be accessed by Base mambers, friends, and derived classes
public:
    int m_public{}; // can be accessed by anybody
};

// Use public inheritance unless you have a specific reason to do otherwise.
class Pub : public Base // note: public inheritance
{
    // Public inheritance means:
    // Public inherited members stay public (so m_public is treated as public)
    // Protected inherited members stay protected (so m_protected is treated as protected)
    // Private inherited members stay inaccessible (so m_private is inaccessible)
public:
    Pub()
    {
        m_public = 1;
        m_protected = 2;
        // m_private = 3; // not allowed: can not access private base members from derived class
    }
};

// Protected: 
// Public -> Protected
// Protected -> Protected
// Private -> Inaccessible
// It is almost never used, except in very particular cases.

class Pri : private Base
{
    // Private inheritance means:
    // Public inherited members become private (so m_public is treated as private)
    // Protected inherited members become private (so m_protected is treated as private)
    // Private inherited members stay inaccessible (so m_private is inaccessible)
    //
    // Private inheritance can be useful when the derived class has no obvious relationship to the base class, 
    // but uses the base class for implementation internally.
    // In practice, private inheritance is rarely used.
public:
    Pri()
    {
        m_public = 1;
        m_protected = 2;
        // m_private = 3; // not allowed: can not access private base members from derived class
    }
};

int main()
{
    Base base;
    base.m_public = 1; // Only public members can be accessed from outside the class
    
    Pri pri;
    // pri.m_public = 1; // not okay: m_public is now private in Pri
    // pri.m_protected = 2; // not okay: m_protected is now private in Pri
    // pri.m_private = 3; // not okay: m_private is inaccessible in Pri

    return 0;
}
