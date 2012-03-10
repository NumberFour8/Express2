#ifndef MATRIX_H
#define MATRIX_H

#include <assert.h>
#include "vector.h"

template <class T>
class Matrix
{
public:
    Matrix(int nRows,int nCols)
    {
        pElem = new T[nRows*nCols];
        memset(pElem,0,nRows*nCols*sizeof(T));
    }

    ~Matrix() { delete[] pElem; }

    int dimension() const { return rows*cols; }
    int getRows() const { return rows; }
    int getCols() const { return cols; }

    T& operator[] (const int& index) const { return pElem[index]; }
    T& operator() (const int i,const int j) const { return pElem[i*cols+j]; }

    Vector<T> operator*(const Vector<T>& V) const
    {
        int sz = V.size();
        assert(sz==cols);

        Vector<T> Ret(sz);
        for (int i = 0;i < sz;++i){
            for (int j = 0;j < sz;++i)
                Ret[i] += V[j]*(*this)(i,j);
        }

        return Ret;
    }

    Matrix<T> operator*(const Matrix<T>& M) const
    {
        assert(M.getRows()==cols);

        Matrix<T> Ret(rows,M.getCols());
        Matrix<T>& A = *this;

        for (int i = 0;i < M.getCols();++i){
           for (int j = 0;j < rows;++j){
             for (int k = 0;k < cols;++k){
                Ret(j,i) = A(j,k)*M(k,i);
             }
           }
        }
        return Ret;
    }

    template <class U>
    friend Matrix<U> operator+(const Matrix<U>& A,const Matrix<U>& B)
    {
        assert(A.dimension()==B.dimension());
        Matrix<U> Ret;
        for (int i = 0;i < A.dimension();++i)
           Ret[i] = A.pElem[i]+B.pElem[i];
        return Ret;
    }

    template <class U>
    friend bool operator==(const Matrix<U>& A,const Matrix<U>& B)
    {
        if (A.dimension() != B.dimension()) return false;
        for (int i = 0;i < A.dimension();++i){
           if (A.pElem[i] != B.pElem[i])
              return false;
        }

        return true;
    }

private:
    T* pElem;
    const int rows,cols;

};

typedef Matrix<double> MatrixD;

#endif // MATRIX_H
