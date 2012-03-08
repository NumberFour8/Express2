#ifndef VECTOR_H
#define VECTOR_H

#include <math.h>

template <class T>
class Vector
{
public:
    Vector(int Size);
    ~Vector();

    T scalarMultiply(const Vector<T>& v) const;
    T magnitude() const;
    int size() const { return nSize; }

    T& operator[](const int& index) { return pElem[index]; }

private:
    T* pElem;
    int nSize;

};

#endif // VECTOR_H
