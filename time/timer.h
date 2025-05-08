#ifndef TIMER_H
#define TIMER_H

#include <chrono> 

class Timer
{
private:
    using Clock = std::chrono::high_resolution_clock;
    using Seconds = std::chrono::duration<double,std::ratio<1>>; // std::ratio<1> means 1 second per tick
    
    std::chrono::time_point<Clock> m_begin{ Clock::now() };

public:
    double elapsed() const
    {
        return std::chrono::duration_cast<Seconds>( Clock::now() - m_begin ).count();
    }

    void reset()
    {
        m_begin = Clock::now();
    }
};

#endif
