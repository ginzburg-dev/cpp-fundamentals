#include <iostream>
#include <string>


// Declare public members first, protected members next, and private members last. 
//This spotlights the public interface and de-emphasizes implementation details.

class Yogurt
{
    std::string m_flavor { "vanilla" };

public:
    void setFlavor(std::string_view flavor)
    {
        m_flavor = flavor;
    }

    const std::string& getFlavor() const { return m_flavor; }
};

void print(const Yogurt& yogurt)
{
    std::cout << "The yogurt has flavor " << yogurt.getFlavor() << '\n';
}

int main()
{
    Yogurt y{};
    y.setFlavor("bubble gum");
    print(y);

    return 0;
}
