#include <iostream>
#include <array>
#include <functional>

template <typename T, std::size_t Row, std::size_t Col>
using Array2d = std::array<std::array<T, Col>, Row>;

template <typename T, std::size_t Row, std::size_t Col>
void printArray(const Array2d<T, Row, Col>& arr)
{
    for ( const auto& i : arr)
    {
        for ( const auto& e : i )
            std::cout << e << ' ';
        
        std::cout << '\n';
    }

    std::cout << '\n';
}

template <typename T, std::size_t Row, std::size_t Col>
constexpr int rowLength( const Array2d<T, Row, Col>&)
{
    return Row;
}

template <typename T, std::size_t Row, std::size_t Col>
constexpr int colLength( const Array2d<T, Row, Col>&)
{
    return Col;
}

template<typename T, std::size_t Row, std::size_t Col>
using ArrayFlat2d = std::array<T, Row*Col >;

template<typename T, std::size_t Row, std::size_t Col>
class ArrayView2d
{
private:
    std::reference_wrapper<ArrayFlat2d<T, Row, Col>> m_arr{};

public:
    ArrayView2d(ArrayFlat2d<T, Row, Col>& arr)
        : m_arr { arr }
    {}

    T& operator()(int row, int col) { return m_arr.get()[ static_cast<std::size_t>(row*cols() + col) ]; };
    const T& operator()(int row, int col) const { return m_arr.get()[ static_cast<std::size_t>(row*cols() + col) ]; };

    T& operator[](int i) { return m_arr.get()[static_cast<std::size_t>(i)]; };
    const T& operator[](int i) const { return m_arr.get()[static_cast<std::size_t>(i)]; };

    int rows() const { return static_cast<int>(Row); };
    int cols() const { return static_cast<int>(Col); };
    int length() const { return static_cast<int>( Row*Col ); };
    void print() const 
    { 
        for(std::size_t row{0}; row < Row; ++row)
        {
            for(std::size_t col{0}; col < Col; ++col)
                std::cout << m_arr.get()[static_cast<std::size_t>(row*cols() + col)] << ' ';
            std::cout << '\n';
        }
        std::cout << '\n';
    }
};

int main()
{
    std::array<std::array<int, 3>, 3> ttt1 {{
        { 1, 2, 3 },
        { 4, 5, 6 },
        { 7, 8, 9 }
    }};

    Array2d<int, 3, 3> ttt2 {{
        { 1, 2, 3 },
        { 4, 5, 6 },
        { 7, 8, 9 }
    }};

    printArray(ttt2);
    std::cout << rowLength(ttt2) << '\n';
    std::cout << colLength(ttt2) << '\n';

    ArrayFlat2d<int, 3, 4> arrFlat {
        1, 2, 3, 4,
        5, 6 , 7, 8,
        9, 10, 11, 12
    };

    ArrayView2d<int, 3, 4> arrView { arrFlat };
    
    std::cout << "Arr[10]: " << arrView[10] << '\n';
    std::cout << "Rows: " << arrView.rows() << " Cols: " << arrView.cols() << " Length: " << arrView.length() << '\n';
    arrView.print();
    arrView[8] = 100;
    arrView(2,1) = 200;
    arrView.print();

    return 0;
}
