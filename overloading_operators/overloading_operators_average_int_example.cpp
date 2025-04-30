#include <iostream>

class Average
{
private:
    std::int32_t m_total{};
    int m_num{};

public:
    Average()
    {}

    friend std::ostream& operator<< (std::ostream& out, const Average& average);
    Average& operator+= (int number);
};

std::ostream& operator<< (std::ostream& out, const Average& average)
{
    auto result = ( average.m_num != 0 ) ? static_cast<double>(average.m_total) / average.m_num : 0.0;
    
    out << result;
    
    return out;
}

Average& Average::operator+= (int number)
{
    m_total += number;
    ++m_num;

    return *this;
}

int main()
{
    Average avg{};
	std::cout << avg << '\n';

	avg += 4;
	std::cout << avg << '\n'; // 4 / 1 = 4

	avg += 8;
	std::cout << avg << '\n'; // (4 + 8) / 2 = 6

	avg += 24;
	std::cout << avg << '\n'; // (4 + 8 + 24) / 3 = 12

	avg += -10;
	std::cout << avg << '\n'; // (4 + 8 + 24 - 10) / 4 = 6.5

	(avg += 6) += 10; // 2 calls chained together
	std::cout << avg << '\n'; // (4 + 8 + 24 - 10 + 6 + 10) / 6 = 7

	Average copy{ avg };
	std::cout << copy << '\n';
    
    return 0;
}
