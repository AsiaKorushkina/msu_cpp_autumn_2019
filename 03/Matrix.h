#include <iostream>

class Matrix
{
    size_t rows;
    size_t cols;
    int** m;
    class Row
    {
        size_t col;
        int* data;
    public:
        Row(size_t _col, int* d): col(_col), data(d){};
        int& operator[](size_t _col){
            if ((_col < 0)||(_col >= col)){
                throw std::out_of_range("out of range");
            }
            return data[_col];
        }
        const int& operator[](size_t _col) const{
            if ((_col < 0)||(_col >= col)){
                throw std::out_of_range("out of range");
            }
            return data[_col];
        }
        
    };
public:
    Matrix(size_t _rows, size_t _cols): rows(_rows), cols(_cols){
        m = new int*[rows];
        for (int i = 0; i < rows; i++){
            m[i] = new int[cols];
        }
    }

    ~Matrix(){
        for (size_t i = 0; i < rows; ++i){
            delete[] m[i];
        }
        delete[] m;
    };

    size_t getRows() const {
        return rows;
    }

    size_t getColumns() const {
        return cols;
    }
    
    Matrix& operator*=(int number){
        for (size_t i = 0; i < rows; i++){
            for (size_t j = 0; j < cols; j++){
                m[i][j] *= number;
            }
        }
        return *this;
    }

    bool operator==(const Matrix& m2) const{
        if ((rows != m2.rows) && (cols != m2.cols)){
            return false;
        }
        for (size_t i = 0; i < rows; i++){
            for (size_t j = 0; j < cols; j++){
                if (m[i][j] != m2[i][j]){
                    return false;
                }
            }
        }
        return true;
    }

    bool operator!=(const Matrix& m2) const{
        return !(*this == m2);
    }

    Row operator[](size_t row){
        if ((row < 0)||(row >= rows)){
            throw std::out_of_range("out of range");
        }
        return Row(cols, m[row]);
    }
    const Row operator[](size_t row) const{
        if ((row < 0)||(row >= rows)){
            throw std::out_of_range("out of range");
        }
        return Row(cols, m[row]);
    }

    friend std::ostream& operator<<(std::ostream& out, const Matrix& m);
};

std::ostream& operator<<(std::ostream &out, const Matrix& m)
{
    for (size_t i = 0; i < m.getRows(); i++){
        for (size_t j = 0; j < m.getColumns(); j++){
            out << m[i][j] <<' ';
        }
        out << std::endl;
    }
 
    return out;
}