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
        pElem = new T[Size]();
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

#endif // VECTOR_H
