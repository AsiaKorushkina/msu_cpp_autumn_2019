#include "Matrix.h"
#include <cassert>

void CHECK_EQ(const Matrix& m1, const Matrix& m2){
    if (m1 != m2){
        std::cout <<"m1 != m2: test failed"<<std::endl;
    }
    else{
        std::cout <<"m1 == m2: test passed"<<std::endl;
    }
}

void CHECK_EQ(int x, int y){
    if (x != y){
        std::cout << x <<" != " <<y << ": test failed"<<std::endl;
    }
    else{
        std::cout << x <<" == " <<y << ": test passed"<<std::endl;
    }
}

void CHECK_OUT_OF_RANGE(const Matrix& m, int i, int j){
    try{
        m[i][j];
        std::cout << "test failed"<<std::endl;
    }
    catch(std::out_of_range& a){
        std::cout << a.what() << " : test passed"<<std::endl;
    }
}


int main(int argc, char const *argv[])
{

	const size_t rows = 5;
	const size_t cols = 4;

	Matrix m1(rows, cols), m2(rows, cols);

	for (size_t i = 0; i < rows; i++){
		for (size_t j = 0; j < cols; j++){
			m1[i][j] = i + j + 1;
            m2[i][j] = m1[i][j];
		}
	}

    CHECK_EQ(m1, m2);
    CHECK_EQ(m1[2][3], 6);

    m2[1][1] = 100;
    CHECK_EQ(m2[1][1], 100);
    
    for (size_t i = 0; i < rows; i++){
        for (size_t j = 0; j < cols; j++){
            m2[i][j] = (i + j + 1) * 3;
        }
    }

    m1 *= 3;
    CHECK_EQ(m1, m2);

    CHECK_EQ(m1.getRows(), rows);
    CHECK_EQ(m1.getColumns(), cols);

    CHECK_OUT_OF_RANGE(m1, -2, 9);
    CHECK_OUT_OF_RANGE(m1, rows, 0);
    CHECK_OUT_OF_RANGE(m1, 0, -2);
    CHECK_OUT_OF_RANGE(m1, 0, cols);

	return 0;
}