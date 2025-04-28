#include <cassert>
#include <iostream>
#include <string>
#include <string_view>

class MyString
{
private:
    std::string m_string{};

public:
    MyString(std::string_view string)
        : m_string{string}
    {}

    std::string_view operator()(int pos, int count);
    friend std::ostream& operator<<(std::ostream& out, const MyString& string);
};

std::string_view MyString::operator()(int pos, int count)
{
    assert( pos >= 0 );
    assert( pos + count <= static_cast<int>(m_string.length()) && "MyString::operator(): Subscripting is out of range." );

    return  std::string_view{ m_string }.substr(
        static_cast<std::string_view::size_type>(pos),
        static_cast<std::string_view::size_type>(count)
    );
}

std::ostream& operator<<(std::ostream& out, const MyString& string)
{
    out << string.m_string;

    return out;
}

int main()
{
    MyString s { "Hello, world!" };
    std::cout << s(7, 5) << '\n'; // start at index 7 and return 5 characters

    return 0;
}
