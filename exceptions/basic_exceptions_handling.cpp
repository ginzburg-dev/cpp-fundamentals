#include <iostream>
#include <string>
#include <string_view>

class CustomException
{
public:
    CustomException() = default;
    CustomException(std::string_view msg) : m_msg{ msg } {}
    ~CustomException() = default;

private:
    std::string m_msg{};
};

int main()
{
    //throw CustomException("Message");
    //throw -1; // throw a literal integer value
    //throw ENUM_INVALID_INDEX; // throw an enum value
    //throw "Can not take square root of negative number"; // throw a literal C-style (const char*) string
    //throw dX; // throw a double variable that was previously defined
    try
    {
        throw "C-String exception";
        std::cout << "This never prints\n";
    }
    catch(const char* c)
    {
        std::cerr << "We caught an exception of type c-string: " << c << '\n';
    }
    catch(double d)
    {
        std::cerr << "An exception of double type has been caught: " << d << '\n';
    }

    std::cout << "Continuing on our merry way\n";
    
    return 0;
}
