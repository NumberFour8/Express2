#ifndef VECTOR_H
#define VECTOR_H

#include <math.h>

template <class T>
class Vector
{
public:
    Vector(int Size) : nSize(Size)
    {  pElem = new T[Size]();   }

    ~Vector() { delete[] pElem;  }

    // Skalární součin dvou vektorů
    T scalarMultiply(const Vector<T>& v) const
    {
        T ret;
        for (int i = 0;i < nSize;++i)
           ret += v[i]*pElem[i];
        return ret;
    }

    T magnitude() const {  return sqrt(scalarMultiply(*this)); } // Velikost vektorů
    int size() const { return nSize; } // Počet složek vektoru

    T& operator[](const int& index) const { return pElem[index]; }

    // Vlastní operátor přiřazení pro deep-copy
    Vector<T>& operator=(const Vector<T>& V)
    {
        if (&V != this){
          if (V.size() == nSize)
              memcpy(pElem,V.pElem,nSize*sizeof(T));
          else {
              delete[] pElem;
              pElem = new T[V.size()];
              memcpy(pElem,V.pElem,V.size()*sizeof(T));
          }
          nSize = V.size();
        }
        return *this;
    }

private:
    T* pElem;
    int nSize;

};

#endif // VECTOR_H
