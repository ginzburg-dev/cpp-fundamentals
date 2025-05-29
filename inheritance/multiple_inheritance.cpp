#include <iostream>
#include <string>
#include <string_view>

// Avoid multiple inheritance unless alternatives lead to more complexity.
// As an interesting aside, you have already been using classes 
// written using multiple inheritance without knowing it: 
// the iostream library objects std::cin and std::cout are both implemented using multiple inheritance!

class Person
{
private:
    std::string m_name{};
    int m_age{};

public:
    Person(std::string_view name, int age)
        : m_name{name}, m_age{age}
    {}

    const std::string& getName() const { return m_name; }
    int getAge() const { return m_age; }
};

class Employee
{
private:
    std::string m_employer{};
    double m_wage{};

public:
    Employee(std::string_view employer, double wage)
        : m_employer{employer}, m_wage{wage}
    {}

    const std::string& getEmployer() const { return m_employer; }
    double getWage() const { return m_wage; }
};

// Teacher publicly inherits Person and Employee
class Teacher : public Person, public Employee 
{
private:
    int m_teacherGrade{};

public:
    Teacher(std::string_view name, int age, std::string_view employer, double wage, int teacherGrade)
        : Person{name, age}, Employee{employer,wage}, m_teacherGrade{teacherGrade}
    {}

    int getTeacherGrade() const { return m_teacherGrade; }
};

// Mixins
struct Point2d
{
    double x{};
    double y{};
};

class Label // mixin Label class
{
public:
    void setText(std::string_view text) { m_text = text; }
    void setFont(int fontSize) { m_fontSize = fontSize; }
private:
    std::string m_text{};
    int m_fontSize{};
};

class Box // mixin Box class
{
public:
    void setTopLeft(Point2d point) { m_topLeft = point; }
    void setBottomRight(Point2d point) { m_bottomRigth = point; }
private:
    Point2d m_topLeft{};
    Point2d m_bottomRigth{};
};

class Tooltip // mixin Tooltip class
{
public:
    void setText(std::string_view text) { m_text = text; }
private:
    std::string m_text{};
};

class Button : public Box, public Label, public Tooltip {}; // Button class uses two mixins

// Curiously Recurring Template Pattern (CRTP).
// This allows the base class (Mixin) to access members of the derived class (Derived) at compile time, 
// enabling patterns like static polymorphism, compile-time type enforcement, or code reuse.
template <class T>
class Mixin
{
    // Mixin<T> can use template type parameter T to access members of Derived
    // via (static_cast<T*>(this))
public:
    void interface()
    {
        static_cast<T*>(this)->implementation();
    }
};

class Derived : public Mixin<Derived>
{
public:
    void implementation()
    {
        std::cout << "Derived implementation\n";
    }
};

int main()
{
    Teacher teacher{"Helen", 25, "Hammersmith College", 50, 8};

    Button button{};
    button.Label::setFont(12);
    button.Label::setText("Start");
    button.Tooltip::setText("Start button"); // Using explicit scope resolution prevents ambiguous calls in mixin methods

    Derived derived{};
    derived.interface();

    return 0;
}
