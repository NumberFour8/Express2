#include "matrix.h"

#include <assert.h>

template<class T>
Matrix<T>::Matrix(int nRows,int nCols) : rows(nRows), cols(nCols)
{
    pElem = new T[nRows*nCols];
    memset(pElem,0,nRows*nCols*sizeof(T));
}

template<class T>
Matrix<T>::~Matrix()
{
    delete[] pElem;
}

template <class T>
Vector<T> Matrix<T>::operator*(const Vector<T>& V) const
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

template<class T>
Matrix<T> Matrix<T>::operator*(const Matrix<T>& M) const
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

template<class U>
Matrix<U> operator+(const Matrix<U>& A,const Matrix<U>& B)
{
    assert(A.dimension()==B.dimension());
    Matrix<U> Ret;
    for (int i = 0;i < A.dimension();++i)
       Ret[i] = A.pElem[i]+B.pElem[i];
    return Ret;
}

template <class U>
bool operator==(const Matrix<U>& A,const Matrix<U>& B)
{
    if (A.dimension() != B.dimension()) return false;
    for (int i = 0;i < A.dimension();++i){
       if (A.pElem[i] != B.pElem[i])
          return false;
    }

    return true;
}
