#include "Matrix.h"
#include <cassert>


int main(int argc, char const *argv[])
{
    const size_t rows = 5;
    const size_t cols = 5;

    Matrix m(rows, cols), m1(rows, cols), m2(rows, cols);

    for (size_t i = 0; i < rows; i++){
        for (size_t j = 0; j < cols; j++){
            m[i][j] = (i + 1) * (j + 1);
            m2[i][j] = m[i][j];
        }
    }

    std::cout << "m" << std::endl;
    std::cout << m << std::endl;

    std::cout << "m1" << std::endl;
    std::cout << m1 <<std::endl;

    std::cout << "m2" << std::endl;
    std::cout << m2 <<std::endl;
    if (m2 == m){
        std::cout << "m2 == m" << std::endl;
    }
    if (m1 != m){
        std::cout << "m1 != m" << std::endl;
    }
    
    assert(m.getRows() == 5);
    assert(m.getColumns() == 5);

    m[1][2] = 105;

    std::cout << "m[1][2] = 5" << std::endl;
    std::cout << m << std::endl;
    double x = m[4][1];

    std::cout << "x = m[4][1] = " << x<<std::endl;

    m *= 3;

    std::cout << "m *= 3" << std::endl;
    std::cout << m << std::endl;
}