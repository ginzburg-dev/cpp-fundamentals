#include <iostream>
#include <vector>
#include <string>
#include <string_view>

struct StudentGrade
{  
    std::string name{};
    char grade{};
};

class GradeMap
{
private:
    std::vector<StudentGrade> m_map{};

public:
    char& operator[](std::string_view name);
};

char& GradeMap::operator[](std::string_view name)
{
    auto found = std::find_if(m_map.begin(), m_map.end(), [&](const auto& student){ return student.name == name; } );
    
    if (found == m_map.end())
    {
        m_map.push_back( StudentGrade{ std::string{name}, '\0' } );
        return m_map.back().grade;
    }
    
    return found->grade;
}

int main()
{
    GradeMap grades{};

    grades["Frank"] = 'A';
    grades["John"] = 'B';

    grades["Frank"] = 'C';

    std::cout << "John: " << grades["John"] << ", " << "Frank: " << grades["Frank"] << '\n';
    
    return 0;
}
