#include <iostream>


// Prefer to implement a function as a non-friend when possible and reasonable.
// In more complex cases, it may be preferable to use friendship instead of adding many new access functions to the interface of a class.

class Humidity; // forward declared so we can use friend non-memeber printWeather() func forward declaration in Temperature class 

class Temperature
{
private:
    double m_temperature { 0 };

public:
    explicit Temperature(double temperature) : m_temperature { temperature } {}

    double getTemperature() const { return m_temperature; }

    friend void printWeatherFriend(const Temperature& t, const Humidity& h); // needed class Humidity; forward declaration
};

class Humidity
{
private:
    double m_humidity { 0 };

public:
    explicit Humidity(double humidity) : m_humidity { humidity } {}
    
    double getHumidity() const { return m_humidity; }

    friend void printWeatherFriend(const Temperature& t, const Humidity& h); // provided access to class members
};

void printWeatherFriend(const Temperature& t, const Humidity& h) // friend. direct access to the class members
{
    std::cout << "The temperature is " << t.m_temperature <<
        " and the humidity is " << h.m_humidity << '\n';         
}

void printWeatherNonFriend(const Temperature& t, const Humidity& h) // use access functions instead of direct access
{
    std::cout << "The temperature is " << t.getTemperature() <<
        " and the humidity is " << h.getHumidity() << '\n';       
}

int main()
{
    Humidity hum { 10 };
    Temperature temp { 12 };

    printWeatherFriend(temp, hum);
    printWeatherNonFriend(temp, hum);

    return 0;
}
