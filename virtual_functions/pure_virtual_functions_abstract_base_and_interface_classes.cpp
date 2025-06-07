#include <iostream>
#include <string>
#include <string_view>

// Any class with one or more pure virtual functions becomes an abstract base class, 
// which means that it can not be instantiated.
// Any derived class must define a body for this function, or that derived class 
// will be considered an abstract base class as well.

class AnimalAbstractBaseClass
{
private:
    std::string m_name{};

public:
    AnimalAbstractBaseClass(std::string_view name)
        : m_name{name}
    {}
    
    const std::string& getName() const { return m_name; }

    virtual std::string_view speak() const = 0; // speak() is a pure virtual function
    virtual std::string_view color() const = 0; // color() is a pure virtual function with definition below

    virtual ~AnimalAbstractBaseClass() = default;    
};

std::string_view AnimalAbstractBaseClass::color() const // definition of pure virtual function color() as an option
{
    return "Default";
}

class Cow : public AnimalAbstractBaseClass
{
public:
    Cow(std::string_view name)
        : AnimalAbstractBaseClass(name)
    {}

    std::string_view speak() const override { // this class is no longer abstract because we defined this function
        return "Moo";
    }
    std::string_view color() const override {
        return AnimalAbstractBaseClass::color(); // use AnimalAbstractBaseClass's default implementation as an option
    }
};

// Interface classes

// An interface class is a class that has no member variables, and where all of the functions are pure virtual
// Interfaces are useful when you want to define the functionality that derived classes must implement, 
// but leave the details of how the derived class implements that functionality entirely up to the derived class.

class ILog
{
public:
    virtual bool openLog(std::string_view filename) = 0;
    virtual bool closeLog() = 0;

    virtual bool writeError(std::string_view errorMessage) = 0;

    virtual ~ILog() {}; // make a virtual destructor in case we delete an ILog pointer, so the proper derived destructor is called
};

class DisplayLog : public ILog
{
public:
    DisplayLog() = default;
    bool openLog(std::string_view filename) override { return true; };
    bool closeLog() override { return true; };
    bool writeError(std::string_view errorMessage) override { return true; };
    ~DisplayLog() override {};
};

class MailLog : public ILog
{
public:
    MailLog() = default;
    bool openLog(std::string_view filename) override { return true; };
    bool closeLog() override { return true; };
    bool writeError(std::string_view errorMessage) override { return true; };
    ~MailLog() override {};
};

void someFunction(int value, ILog& log) // now the caller can pass in any class that conforms to the ILog interface so it makes the function more independent and flexible
{
    if (value < 0)
        log.writeError("Tried to take a value less than zero.");
}

int main()
{
    Cow cow{"Sally"};
    std::cout << cow.speak() << " " << cow.color() << '\n';

    return 0;
}
