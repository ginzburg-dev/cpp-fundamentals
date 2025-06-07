#include <iostream>

class PowerDevice
{
public:
    PowerDevice(int power) { std::cout << "Power device: " << power << '\n'; }
};

class Printer : virtual public PowerDevice
{
public:
    Printer(int printer, int power)
        : PowerDevice{power}
    { 
        std::cout << "Printer: " << printer << '\n'; 
    }
};

class Scanner : virtual public PowerDevice
{
public:
    Scanner(int scanner, int power) 
        : PowerDevice{power}
    { 
        std::cout << "Scanner: " << scanner << '\n';
    }
};

class Copier : public Printer, public Scanner
{
public:
    Copier(int printer, int scanner, int power)
        : PowerDevice{power}, // PoweredDevice is constructed here
        Printer{printer, power}, Scanner{scanner, power}
    {}
};

int main()
{
    Copier copier{ 1, 2, 3 }; // PoweredDevice only gets constructed once
    
    return 0;
}
