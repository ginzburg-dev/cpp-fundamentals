#include <iostream>

struct Advertising
{
    int views {};
    int clicks {};
    double pricePerClick {};
};



void printAdvertising(const Advertising& statics)
{
    std::cout << "VIEWS: " << statics.views << '\n';
    std::cout << "CLICKS %: " << statics.clicks << '\n';
    std::cout << "PRICE PER CLICK: " << statics.pricePerClick << '\n';
    std::cout << "Total Earnings: $" << ( (statics.views * statics.clicks / 100) * statics.pricePerClick ) << " today.\n";
}

int main()
{
    printAdvertising({10,20,0.5});
    
    return 0;
}
