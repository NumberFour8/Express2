#ifndef LOADER_H
#define LOADER_H

#include <math.h>
#include <iostream>
#include <fstream>
#include <locale>
using namespace std;

#include "linkedlist.h"
#include "matrix.h"

// Třída pro načítání transformací
class Loader
{
public:
    enum TransformType { ttTranslate = 1, ttRotate = 2, ttScale = 3, ttIdentity = 4, ttUnknown = 0};
    struct Transform {
        Matrix<float> T;
        TransformType type;
        double p1,p2;
        Transform() : T(3,3) { type = ttUnknown; p1 = p2 = 0; }
    };

    Loader() : transforms() { }
    ~Loader();

    bool load(const char* szFile,int ScalingFactor);
    LinkedList<Transform>& getTransforms() { return transforms; }

    static const char* getTransformString(TransformType Type);
    static TransformType getTransformType(string Name);
private:
    LinkedList<Transform> transforms;

};

#endif // LOADER_H
