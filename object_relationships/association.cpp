#include <iostream>
#include <vector>
#include <string>
#include <string_view>
#include <functional>

// Association = loose link: no ownership, objects are unrelated, can be uni- or bidirectional.
// Aggregation = "has-a" without ownership, always unidirectional.
// Composition = "owns-a", strong ownership, lifetime tied.

class Patient;

class Doctor
{
private:
    std::string m_name{};
    std::vector<std::reference_wrapper<Patient>> m_patients{};

public:
    Doctor(std::string_view name)
        : m_name{name}
    {}

    void addPatient(Patient& patient);
    friend std::ostream& operator<< (std::ostream& out, const Doctor& doctor);
    const std::string getName() const { return m_name; }
};

class Patient
{
private:
    std::string m_name{};
    std::vector<std::reference_wrapper<Doctor>> m_doctors{};

    void addDoctor(Doctor& doctor)
    {
        m_doctors.push_back(doctor);
    }

public:
    Patient(std::string_view name)
        : m_name{name}
    {}

    friend std::ostream& operator<< (std::ostream& out, const Patient& patient);
    const std::string getName() const { return m_name; }
    friend void Doctor::addPatient(Patient& patient);
};

void Doctor::addPatient(Patient& patient)
{
    m_patients.push_back(patient);
    patient.addDoctor(*this);
}

std::ostream& operator<< (std::ostream& out, const Doctor& doctor)
{
    out << "Doctor " << doctor.m_name;
    if(doctor.m_patients.empty())
    {
        out << " has no patients right now.\n";
        return out;
    }

    out << " is seeing patients: ";
    for (const auto& i : doctor.m_patients)
        out << i.get().getName() << ' ';
    return out;
}

std::ostream& operator<< (std::ostream& out, const Patient& patient)
{
    out << "Patient " << patient.m_name;
    if(patient.m_doctors.empty())
    {
        out << " has no doctors right now.\n";
        return out;
    }

    out << " is seeing doctors: ";
    for (const auto& i : patient.m_doctors)
        out << i.get().getName() << ' ';
    return out;
}

// Reflexive association (relationships with other objects of the same type)
class Course
{
private:
    std::string m_name{};
    const Course* m_prerequisite{};

private:
    Course(std::string_view name, const Course* prerequisite = nullptr)
        : m_name{name}, m_prerequisite{prerequisite}
    {}

};

// Indirect associations
class Car
{
private:
    std::string m_name{};
    int m_id{};
public:
    Car(std::string name, int id)
        : m_name{name}, m_id{id}
    {}

    const std::string& getName() const { return m_name; }
    const int getId() const { return m_id; }
};

class Driver
{
private:
    std::string m_name{};
    int m_carId{};

public:
    Driver(std::string name, int carId)
        : m_name{name}, m_carId{carId}
    {}

    const std::string& getName() const { return m_name; }
    const int getCarId() const { return m_carId; }
};

namespace CarLot
{
    Car carLot[4] {
        { "Corolla", 1 },
        { "Prius", 2 },
        { "Matrix", 3 },
        { "Accord", 4 },
    };

    Car* getCar(int id)
    {
        for ( auto& i : carLot )
            if ( i.getId() == id )
                return &i;
        return nullptr;
    }
}

int main()
{

    Patient dan{ "Dan" };
    Patient john{ "John" };
    Patient ann{ "Ann" };

    Doctor drJames{ "James" };
    Doctor drScott{ "Scott" };

    drJames.addPatient(dan);
    drScott.addPatient(john);
    drScott.addPatient(ann);

    std::cout << drJames << '\n';
    std::cout << drScott << '\n';
    std::cout << dan << '\n';
    std::cout << john << '\n';
    std::cout << ann << '\n';

    // Indirect associations

    Driver driver{"Hanz", 1};

    Car* car{ CarLot::getCar(driver.getCarId()) };

    if (car)
        std::cout << driver.getName() << " is driving a " << car->getName() << '\n';
    else
        std::cout << driver.getName() << " couldn't find his car\n";

    return 0;
}
