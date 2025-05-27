#include <iostream>

struct CPU
{
    int m_model{};
    int m_nCores{};

    CPU(int model=0, int nCores=0)
        : m_model{model}, m_nCores{nCores}
    {}
};

class Base
{
private:
    const double m_const_double;
    CPU& m_cpu;

public:
    Base(const double const_double, CPU& cpu)
        : m_const_double{const_double}, m_cpu{cpu}
    {}

    CPU& getCPU() { return m_cpu; }
};

int main()
{
    CPU core{ 1243, 8 };

    Base base{ 12.3, core };
    std::cout << base.getCPU().m_model << '\n';
    return 0;
}
