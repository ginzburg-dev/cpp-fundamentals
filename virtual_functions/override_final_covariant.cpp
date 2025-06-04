#include <iostream>
#include <string>
#include <string_view>


// Use the virtual keyword on virtual functions in a base class.
//
// Use the override specifier (but not the virtual keyword) on override functions in derived classes. 
// This includes virtual destructors.
//
// If a function marked as override does not override a base class function 
// (or is applied to a non-virtual function), the compiler will flag the function as an error.
// 
// If a member function is both const and an override, the const must be listed first. 
// const override is correct, override const is not.
//
// 'override final' keyword makes this function not able to be overridden in derived classes
//
// Covariant return types are often used in cases where a virtual member function returns a pointer or reference to 
// the class containing the member function (e.g. Base::getThis() returns a Base*, 
// and Derived::getThis() returns a Derived*). 

class Base
{
public:
    virtual std::string_view getName1(int x) { return "A"; };
    virtual std::string_view getName2(int x) { return "A"; };
    virtual std::string_view getName3(int x) { return "A"; };
};

class Derived : public Base
{
public:
    // std::string_view getName1(int x) override { return "B" };            // Compile error: function is not an override 
    // std::string_view getName2(int x) const  override { return "B" };     // Compile error: function is not an override
    std::string_view getName3(int x) override final { return "B"; };  // we use 'final' to prevent the getName3 function from being overriden in derived classes
};

class C : public Derived
{
public:
    // std::string_view getName3(int x) override { return "C"; }; // Compile error: overrides Derived::getName3(), which is final 
};

class D final : public Base // note use of final specifier here
{
public:
    std::string_view getName3(int x) override { return "D"; };
};

/*
class F : public D // compile error: cannot inherit from final class
{
public:
    std::string_view getName3(int x) override { return "F"; };
};
*/

// Covariant return types

class Base1
{
public: 
    virtual Base1* getThis() { std::cout << "called Base1::getThis()\n"; return this; }
    void printType() { std::cout << "return a Base1\n"; }
};

class Derived1 : public Base1
{
public: 
    Derived1* getThis() override { std::cout << "called Derived1::getThis()\n"; return this; }
    void printType() { std::cout << "return a Derived1\n"; }
};

// // Covariant return types, example 2

class Asset
{
public:
    virtual Asset* clone() const 
    {
        return new Asset(*this);
    }

    virtual void printInfo() const { std::cout << "Asset\n"; }
    void nonVirtualPrintInfo() const  { std::cout << "Asset\n"; }
};

class Texture : public Asset
{
public:
    Texture* clone() const override
    {
        return new Texture(*this);
    }

    void printInfo() const override { std::cout << "Texture\n"; }
    void nonVirtualPrintInfo() const  { std::cout << "Texture\n"; }
};

int main()
{
    Derived1 d{};
    Base1* b{ &d };
    d.getThis()->printType(); // calls Derived1::getThis(), returns a Derived1*, calls Derived1::printType
    b->getThis()->printType(); // calls Derived1::getThis(), the returned Derived1* is upcast to a Base1* because printType() isn't virtual, calls Base1::printType
    
    Asset* asset = new Texture;
    asset->printInfo(); // Prints: Texture
    asset->nonVirtualPrintInfo(); // Prints: Asset, because this function isn't virtual

    Texture* texture { dynamic_cast<Texture*>(asset) };
    texture->printInfo(); // Prints: Texture

    asset = new Asset;
    asset->printInfo(); // Prints: Asset

    return 0;
}
