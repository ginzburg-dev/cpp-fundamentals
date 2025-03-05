#include <iostream>

class outer; // ok: can forward-declare non-nested type
//class outer::inner1; // error: can't forward deflare nested type prior to outer class definition

class outer
{
public:
    class inner1 // note: nested type declared here
    {
    };
};

class Fruit
{
public:
    // Define any nested types at the top of your class type.
    enum Type
    {
        apple,
        banana,
        cherry,
    };

    using IDType = int; // type alias

    class Seed
    {
    public:
        void printFruitType(const Fruit& f) const // can't access Fruit's `this` pointer so we can't print m_name and m_type directly
        {
            std::cout << f.m_type << '\n';
        }
    };

    class inner1; // forward declaration inside the enclosing class. nested since it defined inside enclosed class
    class inner1 // declaration of forward declared type inside the enclosing class
    {
    };
    class inner2; // forward declaration inside the enclosing class. it's not a nested class inside Fruit! non-nested, global forward declaration

private:
    Type m_type {};
    int m_percentageEaten { 0 };
    IDType m_id { 1 }; // inside the class we can just use IDType without scope qualifier

public:
    Fruit(Type type, IDType id)
        : m_type{ type }
        , m_id { id }
    {
    }

    Type getType() const { return m_type; }
    int getPercentageEaten() const { return m_percentageEaten; }
    IDType getID() const { return m_id; }

    bool isCherry() const { return m_type == cherry; }
};

class inner2
{
};

int main()
{
    Fruit apple { Fruit::apple, 2 };

    if ( apple.getType() == Fruit::apple )
        std::cout << "It's an apple.\n";
    else
        std::cout << "It's not an apple.\n";

    Fruit::IDType id { apple.getID() }; // must use fully qualifief name outside the class
    std::cout << id << '\n';
        
    Fruit::Seed seed {};
    seed.printFruitType(apple);

    return 0;
}
