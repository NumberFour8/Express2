#ifndef LOADER_H
#define LOADER_H

#include <math.h>
#include <iostream>
#include <fstream>
using namespace std;

#include "linkedlist.h"
#include "matrix.h"

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

    Loader(const char* szFile,int ScalingFactor);
    ~Loader();

    LinkedList<Transform>& getTransforms() { return transforms; }

    static const char* getTransformString(TransformType Type);
    static TransformType getTransformType(string Name);
private:
    LinkedList<Transform> transforms;

};

#endif // LOADER_H
