#ifndef MATRIX_H
#define MATRIX_H

#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "vector.h"

template <class T>
class Matrix
{
public:
    Matrix(int nRows,int nCols)
    {
        rows = nRows, cols = nCols;
        pElem = new T[nRows*nCols]();
    }

    ~Matrix() { delete[] pElem; }

    int dimension() const { return rows*cols; }
    int getRows() const { return rows; }
    int getCols() const { return cols; }

    // Vytvoří jednotkovou matici
    void identity()
    {
        assert(cols==rows);
        for (int i = 0;i < rows;++i)
           operator()(i,i) = 1;
    }

    T& operator[] (const int& index) const { return pElem[index]; }
    T& operator() (const int i,const int j) const { return getElem(i,j); }

    // Násobení matice vektorem
    Vector<T> operator*(Vector<T>& V) const
    {
        int sz = V.size();
        assert(sz==cols);

        Vector<T> Ret(sz);
        for (int i = 0;i < sz;++i){
            for (int j = 0;j < sz;++j)
                Ret[i] += V[j]*getElem(i,j);
        }

        return Ret;
    }

    // Násobení matice s maticí (není obecně komutativní)
    Matrix<T> operator*(const Matrix<T>& M) const
    {
        assert(M.getRows()==cols);

        Matrix<T> Ret(rows,M.getCols());
        for (int i = 0;i < rows;i++){
           for (int j = 0; j < M.getCols(); j++){
              for (int k = 0; k < cols; k++)
                 Ret(i, j) += getElem(i, k) * M(k, j);
           }
        }

        return Ret;
    }

    // Vlastní operátor přiřazení pro deep-copy
    Matrix<T>& operator=(const Matrix<T>& M)
    {
        if (&M != this){
          if (M.dimension() == rows*cols)
              memcpy(pElem,M.pElem,rows*cols*sizeof(T));
          else {
              delete[] pElem;
              pElem = new T[M.dimension()];
              memcpy(pElem,M.pElem,M.dimension()*sizeof(T));
          }
          rows = M.getRows();
          cols = M.getCols();
        }
        return *this;
    }

    // Spřátelené sčítání matic (komutativní)
    template <class U>
    friend Matrix<U> operator+(const Matrix<U>& A,const Matrix<U>& B)
    {
        assert(A.dimension()==B.dimension());

        Matrix<U> Ret;
        for (int i = 0;i < A.dimension();++i)
           Ret[i] = A.pElem[i]+B.pElem[i];
        return Ret;
    }

    // Spřátelené porovnání matic
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
    int rows,cols;

    // Vnitřní inline metoda pro přepočet souřadnic do 1D pole
    inline T& getElem(const int i,const int j) const { return pElem[i*cols+j]; }
};

#endif // MATRIX_H
