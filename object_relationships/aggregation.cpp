#include <iostream>
#include <vector>
#include <functional>
#include <string>
#include <string_view>
#include <memory>

// Aggregations:
// "Has-a" relationship where the container (class) holds references or pointers
// to external objects it does NOT own. The lifetime of the parts is managed outside.
//
// Typically use pointer or reference members that point to or reference objects 
// that live outside the scope of the aggregate class
// Not responsible for creating/destroying parts

class Teacher
{
private:
    std::string m_name{};

public:
    Teacher(std::string_view name)
        : m_name{name}
    {}

    const std::string& getName() const { return m_name; }
};

class Department
{
private:
    const Teacher& m_teacher; // holds a reference,

public:
    Department(const Teacher& teacher)
        : m_teacher{teacher} // initialize the reference in the initializer list
    {}
};

class DepartmentModern
{
private:
    std::vector<std::reference_wrapper<Teacher>> m_teachers{};

public:
    DepartmentModern()
    {}

    void add(Teacher& teacher) { m_teachers.emplace_back(teacher); };

    friend std::ostream& operator<< (std::ostream& out, const DepartmentModern& dept)
    {
        out << "Department: ";
        for (const auto& i : dept.m_teachers )
            out << i.get().getName() << ' ';
        out << '\n';

        return out;
    }
};

int main()
{
    Teacher john{ "John" };
    {
        Department dept{ john };
    }

    std::cout << john.getName() << " still exists!\n";

    // std::rederence_wrapper

    std::reference_wrapper<Teacher> teacher_wrapped_ref{ john };
    std::cout << "teacher_wrapped_ref holds a reference to " << teacher_wrapped_ref.get().getName() << '\n';

    Teacher hannah{ "Hannah" };
    teacher_wrapped_ref = hannah;
    std::cout << "teacher_wrapped_ref holds a reference to " << teacher_wrapped_ref.get().getName() << '\n';


    std::vector<std::reference_wrapper<const Teacher>> teachers{ john, hannah };

    Teacher kail{ "Kail" };
    Teacher luisa{ "Luisa" };

    teachers.push_back(kail);     // creates temp Teacher, then moves/copies
    teachers.emplace_back(kail);  // constructs Teacher using 'kail' as constructor arg
    teachers[std::size(teachers)-1] = std::cref(luisa); // using std::ref() or cref

    for (const auto& i : teachers)
        std::cout << i.get().getName() << ' ';
    std::cout << '\n';

    // Example: DepartmentModern

    Teacher t1{ "Bob" };
    Teacher t2{ "Frank" };
    Teacher t3{ "Beth" };

    {
        // Create a department and add some Teachers to it
        DepartmentModern department{}; // create an empty Department

        department.add(t1);
        department.add(t2);
        department.add(t3);

        std::cout << department;
    }
     // department goes out of scope here and is destroyed

    std::cout << t1.getName() << " still exists!\n";
    std::cout << t2.getName() << " still exists!\n";
    std::cout << t3.getName() << " still exists!\n";
    
    return 0;
}
