#ifndef CREATURE_H
#define CREATURE_H

#include "point2d.h"
#include <iostream>
#include <string>
#include <string_view>

class Creature
{
private:
    std::string m_name{};
    Point2D m_location{};

public:
    Creature(std::string_view name, const Point2D& location)
        : m_name{name}, m_location{location}
    {}

    friend std::ostream& operator<< (std::ostream& out, const Creature& creature)
    {
        out << creature.m_name << " is at " << creature.m_location;
        return out;
    }

    void move(int x, int y)
    {
        m_location.set(x, y);
    }
};

#endif
