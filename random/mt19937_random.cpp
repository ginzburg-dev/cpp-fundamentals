#include <iostream>
#include <random>
#include <chrono>

int main()
{
    std::mt19937 mt{ static_cast<std::mt19937::result_type>( 
        std::chrono::steady_clock::now().time_since_epoch().count() ) 
        }; // seed a 32-bit Mersenne Twister usind steady_clock

    std::mt19937 mt_rd{ std::random_device{}() }; // seeding by random_device{}.operator()

    std::random_device rd{};
    std::seed_seq ss{ rd(), rd(), rd(), rd(),  rd(), rd(), rd(), rd()}; // warming up our PRNG
    std::mt19937 mt_ss{ std::random_device{}() }; // seeding by seed sequence of 8 random_device values

    std::uniform_int_distribution<> die6{1, 6};

    // steady_clock
    for (int i{ 1 }; i <= 50; ++i)
    {
        std::cout << die6(mt) << '\t'; // generate a random number
        if (i % 5 == 0) // if we've printed 5, start a new row
            std::cout << '\n';
    }

    std::cout << '\n';

    // random device
    for (int i{ 1 }; i <= 50; ++i)
    {
        std::cout << die6(mt_rd) << '\t'; // generate a random number
        if (i % 5 == 0) // if we've printed 5, start a new row
            std::cout << '\n';
    }

    std::cout << '\n';

    // seed sequence
    for (int i{ 1 }; i <= 50; ++i)
    {
        std::cout << die6(mt_ss) << '\t'; // generate a random number
        if (i % 5 == 0) // if we've printed 5, start a new row
            std::cout << '\n';
    }


    return 0;
}
