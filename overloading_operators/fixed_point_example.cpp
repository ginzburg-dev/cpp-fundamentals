#include <iostream>
#include <cmath>

class FixedPoint2
{
private:
    std::int16_t m_base{};
    std::int8_t m_decimal{};

public:
    FixedPoint2(std::int16_t base=0, std::int8_t decimal=0)
        : m_base{ base }, m_decimal{ decimal }
    {
        if ( m_base < 0 || m_decimal < 0 )
        {
            if ( m_base > 0 )
                m_base = -m_base;

            if ( m_decimal > 0 )
                m_decimal = -m_decimal;
        }

        m_base += m_decimal / 100;
        m_decimal = m_decimal % 100;
    }

    FixedPoint2(double fp) :
        FixedPoint2(
            static_cast<std::int16_t>(std::trunc(fp)),
            static_cast<std::int8_t>(std::round(fp * 100) - std::trunc(fp) * 100 )
        )
    {}

    explicit operator double() const;
    friend bool operator== (const FixedPoint2& fp1, const FixedPoint2& fp2 );
    FixedPoint2 operator-() const;

    friend std::ostream& operator<< (std::ostream& out, const FixedPoint2& fp);
    friend std::istream& operator>> (std::istream& out, FixedPoint2& fp);
    friend bool testDecimal(const FixedPoint2& fp);
};

FixedPoint2::operator double() const
{
    return m_base + ( static_cast<double>(m_decimal)/100 );
}

FixedPoint2 operator+ (const FixedPoint2& fp1, const FixedPoint2& fp2)
{
    return FixedPoint2{ static_cast<double>(fp1) + static_cast<double>(fp2) };
}

bool operator== (const FixedPoint2& fp1, const FixedPoint2& fp2 )
{
    return fp1.m_base == fp2.m_base && fp1.m_decimal == fp2.m_decimal;
}

FixedPoint2 FixedPoint2::operator-() const
{
    return FixedPoint2{ -static_cast<double>(*this) };
}

std::ostream& operator<< (std::ostream& out, const FixedPoint2& fp)
{
    out << static_cast<double>(fp);
    return out;
}

std::istream& operator>> (std::istream& in, FixedPoint2& fp)
{
    double input{};
    in >> input;
    fp = FixedPoint2{ input };

    return in;
}

bool testDecimal(const FixedPoint2& fp)
{
    if (fp.m_base >= 0)
        return fp.m_decimal >= 0 && fp.m_decimal < 100;
    else
        return fp.m_decimal <= 0 && fp.m_decimal > -100;
}

int main()
{
	assert(FixedPoint2{ 0.75 } == FixedPoint2{ 0.75 });    // Test equality true
	assert(!(FixedPoint2{ 0.75 } == FixedPoint2{ 0.76 })); // Test equality false

	// Test additional cases -- h/t to reader Sharjeel Safdar for these test cases
	assert(FixedPoint2{ 0.75 } + FixedPoint2{ 1.23 } == FixedPoint2{ 1.98 });    // both positive, no decimal overflow
	assert(FixedPoint2{ 0.75 } + FixedPoint2{ 1.50 } == FixedPoint2{ 2.25 });    // both positive, with decimal overflow
	assert(FixedPoint2{ -0.75 } + FixedPoint2{ -1.23 } == FixedPoint2{ -1.98 }); // both negative, no decimal overflow
	assert(FixedPoint2{ -0.75 } + FixedPoint2{ -1.50 } == FixedPoint2{ -2.25 }); // both negative, with decimal overflow
	assert(FixedPoint2{ 0.75 } + FixedPoint2{ -1.23 } == FixedPoint2{ -0.48 });  // second negative, no decimal overflow
	assert(FixedPoint2{ 0.75 } + FixedPoint2{ -1.50 } == FixedPoint2{ -0.75 });  // second negative, possible decimal overflow
	assert(FixedPoint2{ -0.75 } + FixedPoint2{ 1.23 } == FixedPoint2{ 0.48 });   // first negative, no decimal overflow
	assert(FixedPoint2{ -0.75 } + FixedPoint2{ 1.50 } == FixedPoint2{ 0.75 });   // first negative, possible decimal overflow

	FixedPoint2 a{ -0.48 };
	assert(static_cast<double>(a) == -0.48);
	assert(static_cast<double>(-a) == 0.48);

	std::cout << "Enter a number: "; // enter 5.678
	std::cin >> a;
	std::cout << "You entered: " << a << '\n';
	assert(static_cast<double>(a) == 5.68);
    
    return 0;
}
