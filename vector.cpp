#include "vector.h"

template <class T>
Vector<T>::Vector(int Size) : nSize(Size)
{
    pElem = new T[Size];
    memset(pElem,0,Size*sizeof(T));
}

template<class T>
Vector<T>::~Vector()
{
    delete[] pElem;
}

template<class T>
T Vector<T>::scalarMultiply(const Vector<T>& v) const
{
    T ret;
    for (int i = 0;i < nSize;++i)
       ret += v[i]*pElem[i];
    return ret;
}

template <class T>
T Vector<T>::magnitude() const
{
    return sqrt(scalarMultiply(*this));
}
