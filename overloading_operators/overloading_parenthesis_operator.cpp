#include <iostream>
#include <cassert>

class Matrix
{
private:
    double m_matrix[4][4]{};

public:
    double& operator()(int i, int j);
    const double& operator()(int i, int j) const;
    
};

double& Matrix::operator()(int i, int j) 
{
    assert(i >= 0 && i < 4 );
    assert(j >= 0 && j < 4 );

    return m_matrix[i][j];
}

const double& Matrix::operator()(int i, int j) const
{
    assert(i >= 0 && i < 4 );
    assert(j >= 0 && j < 4 );

    return m_matrix[i][j];
}

int main()
{
    return 0;
}
