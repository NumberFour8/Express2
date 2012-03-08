#ifndef MATRIX_H
#define MATRIX_H


#include "vector.h"

template <class T>
class Matrix
{
public:
    Matrix(int nRows,int nCols);
    ~Matrix();

    int dimension() const { return rows*cols; }
    int getRows() const { return rows; }
    int getCols() const { return cols; }

    T& operator[] (const int& index) const { return pElem[index]; }
    T& operator() (const int i,const int j) const { return pElem[i*cols+j]; }

    Vector<T> operator*(const Vector<T>& V) const;
    Matrix<T> operator*(const Matrix<T>& M) const;

    template <class U>
    friend Matrix<U> operator+(const Matrix<U>& A,const Matrix<U>& B);

    template <class U>
    friend bool operator==(const Matrix<U>& A,const Matrix<U>& B);
private:
    T* pElem;
    const int rows,cols;

};

#endif // MATRIX_H
