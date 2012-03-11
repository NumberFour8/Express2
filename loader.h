#ifndef LOADER_H
#define LOADER_H

#include <math.h>
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

#include "linkedlist.h"
#include "matrix.h"

class Loader
{
public:
    Loader(const char* szFile);

    LinkedList<MatrixD>& getTransforms() { return transforms; }

private:
    LinkedList<MatrixD> transforms;

};

#endif // LOADER_H
