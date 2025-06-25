#include <algorithm>
#include <iostream>
#include <vector>
#include <memory>

class Shape
{
public:
    virtual std::ostream& print(std::ostream& out) const = 0;

    friend std::ostream& operator<<(std::ostream& out, const Shape& s)
    {
        return s.print(out);
    }
    virtual ~Shape() = default;
};

struct Point
{
    int x{};
    int y{};

    friend std::ostream& operator<<(std::ostream& out, const Point& p)
    {
        out << "Point(" << p.x << ", " << p.y << ")";
        return out;
    }   
};

class Triangle : public Shape
{
private:
    Point m_p1;
    Point m_p2;
    Point m_p3;

public:
    Triangle(const Point& p1, const Point& p2, const Point& p3)
        : m_p1{ p1 }, m_p2{ p2 }, m_p3{ p3 }
    {}

    std::ostream& print(std::ostream& out) const override
    {
        out << "Triangle(" << m_p1 << ", " << m_p2 << ", " << m_p3 << ")";
        return out;
    }

    ~Triangle() override {};
};

class Circle : public Shape
{
private:
    Point m_pCenter{};
    int m_radius{};
public:
    Circle(const Point& pCentre, int radius)
        : m_pCenter{ pCentre }, m_radius{ radius }
    {}

    std::ostream& print(std::ostream& out) const override
    {
        out << "Circle(" << m_pCenter << ", " << m_radius << ")";
        return out;
    }

    int getRadius() const { return m_radius; }

    ~Circle() override {};
};

template<typename T>
int getLargestRadius(const T& v)
{
    int largeRadius{0};
    
    for (const auto* e : v)
    {
        if (auto* circle{ dynamic_cast<const Circle*>(e) })
        {
            largeRadius = std::max(largeRadius, circle->getRadius());
        }
    }

    return largeRadius;
}

template<typename T>
int getLargestRadius_unq(const T& v)
{
    int largeRadius{0};
    
    for (const auto& e : v)
    {
        if (auto* circle = dynamic_cast<const Circle*>(e.get()))
        {
            largeRadius = std::max(largeRadius, circle->getRadius());
        }
    }

    return largeRadius;
}

int main()
{
    std::vector<Shape*> v{
        new Circle{Point{1, 2}, 7},
        new Triangle{Point{ 1, 2 }, Point{ 3, 4 }, Point{ 5, 6 }},
        new Circle{Point{7, 8}, 3}
    };

    for (const auto* e : v)
        std::cout << *e << '\n';
    
    int maxRadius{getLargestRadius(v)};

    std::cout << "Largest radius is " << maxRadius << '\n';

    for (const auto* e : v)
        delete e;


    // Unique_ptr

    std::vector<std::unique_ptr<Shape>> v_unq{};
    v_unq.reserve(3);
    v_unq.push_back(std::make_unique<Circle>(Point{1, 2}, 7));
    v_unq.push_back(std::make_unique<Triangle>(Point{ 1, 2 }, Point{ 3, 4 }, Point{ 5, 6 }));
    v_unq.push_back(std::make_unique<Circle>(Point{7, 8}, 3));

    for (const auto& e : v_unq)
        std::cout << *e << '\n';
    
    int maxRadius_unq{getLargestRadius_unq(v_unq)};

    std::cout << "Largest radius is " << maxRadius_unq << '\n';

    return 0;
}
