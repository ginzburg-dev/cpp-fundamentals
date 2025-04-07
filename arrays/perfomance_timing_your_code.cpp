#include <chrono>
#include <algorithm>
#include <iostream>

class Timer
{
private:
    using Clock = std::chrono::steady_clock;
    using Second = std::chrono::duration<double, std::ratio<1>>;

    std::chrono::time_point<Clock> m_begin { Clock::now() };

public:
    void reset()
    {
        m_begin = Clock::now();
    }

    double elapsed() const
    {
        return std::chrono::duration_cast<Second>(Clock::now() - m_begin ).count(); 
    }
};

int main()
{

    int array[] { 100, 39, 2, 595, 3, 4 };

    constexpr int length { static_cast<int>(std::size(array)) };

    Timer t{};

    for (int startIndex{0}; startIndex < length - 1; ++startIndex)
    {
        int smallestIndex{ startIndex };

        for ( int currentIndex{ startIndex + 1 }; currentIndex < length; ++currentIndex )
        {
            if ( array[currentIndex] < array[smallestIndex] )
                smallestIndex = currentIndex;
        }

        std::swap(array[startIndex], array[smallestIndex]);
    }

    std::cout << "Selection sort from user: " << t.elapsed() << "s.\n";

    int array1[] { 100, 39, 2, 595, 3, 4 };

    t.reset();

    std::sort(std::begin(array1), std::end(array1));

    std::cout << "Selection sort (standard library) : " << t.elapsed() << "s.\n";

    return 0;
}
