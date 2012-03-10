#ifndef VECTOR_H
#define VECTOR_H

#include <math.h>

template <class T>
class Vector
{
public:
    Vector(int Size)
    {
        pElem = new T[Size];
        memset(pElem,0,Size*sizeof(T));
    }

    ~Vector() { delete[] pElem;  }

    T scalarMultiply(const Vector<T>& v) const
    {
        T ret;
        for (int i = 0;i < nSize;++i)
           ret += v[i]*pElem[i];
        return ret;
    }

    T magnitude() const {  return sqrt(scalarMultiply(*this)); }
    int size() const { return nSize; }

    T& operator[](const int& index) { return pElem[index]; }

private:
    T* pElem;
    int nSize;

};

typedef Vector<double> VectorD;

#endif // VECTOR_H
