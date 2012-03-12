#ifndef VECTOR_H
#define VECTOR_H

#include <math.h>
#include <cstdarg>

template <class T>
class Vector
{
public:
    Vector(int Size) : nSize(Size)
    {
        pElem = new T[Size];
        memset(pElem,0,Size*sizeof(T));
    }

    Vector(int Size,...) : nSize(Size)
    {
        pElem = new T[Size];
        memset(pElem,0,Size*sizeof(T));

        va_list vals;
        va_start(vals,Size);
        for (int i = 0;i < Size;++i)
            pElem[i] = va_arg(vals,T);
        va_end(vals);
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
