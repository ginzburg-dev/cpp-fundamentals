#include <iostream>
#include <cstring> // for strlen()
#include <cassert>

class MyString
{
private:
    int m_length{};
    char* m_data{};

public:
    MyString(const char* source = "")
    {
        assert(source);

        m_length = std::strlen(source) + 1;
        m_data = new char[m_length];

        for (int i{0}; i < m_length; ++i)
            m_data[i] = source[i];
    }
    // Copy constructor
    MyString(const MyString& source);

    ~MyString()
    {
        delete[] m_data;
    }

    MyString& operator=(const MyString& source)
    {
        if (this != &source)
        {
            deepCopy(source);
        }

        return *this;
    }

    void deepCopy(const MyString& source);

    char* getString() { return m_data; }
    int getLength() { return m_length; }
};

void MyString::deepCopy(const MyString& source)
{
    delete[] m_data;
    m_length = source.m_length;

    if (source.m_data)
    {
        m_data = new char[m_length];

        for (int i{0}; i < m_length; ++i)
            m_data[i] = source.m_data[i];
    }
    else
        m_data = nullptr;
}

MyString::MyString(const MyString& source)
{
    deepCopy(source);
}

int main()
{
    MyString str1{"Hello World!"};
    MyString str2{ str1 };

    {
        MyString str3{ str2 };
    }

    std::cout << str1.getString() << ' ' << str2.getString() << '\n';

    return 0;
}
