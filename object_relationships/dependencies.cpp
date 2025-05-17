#include <iostream>
#include <string>
#include <string_view>

class Logger
{
public:
    void log(std::string_view msg)
    {
        std::cout << "Saved to log: " << msg << '\n';
    }
};

class App
{
public:
    void run(Logger& logger) // class App depends on class Logger
    {
        logger.log("App started");
    }
};

int main()
{
    return 0;
}
