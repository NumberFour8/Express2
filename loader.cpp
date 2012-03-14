#include "loader.h"

Loader::Loader(const char* szFile,int ScalingFactor) : transforms()
{
    ifstream file;
    file.open(szFile);

    if (file.is_open())
    {
        string cmd;
        while(file.good()){
            cmd.clear();
            file >> cmd;

            TransformType tt = getTransformType(cmd);
            if (tt == ttUnknown) continue;

            Transform *Tr = new Transform;
            Tr->type = tt;

            switch (tt) {
                case ttTranslate:
                    file >> Tr->p1 >> Tr->p2;

                    Tr->T(0,0) = 1; Tr->T(0,1) = 0; Tr->T(0,2) = Tr->p1*ScalingFactor;
                    Tr->T(1,0) = 0; Tr->T(1,1) = 1; Tr->T(1,2) = Tr->p2*ScalingFactor;
                    Tr->T(2,0) = 0; Tr->T(2,1) = 0; Tr->T(2,2) = 1;
                break;
                case ttRotate:
                    file >> Tr->p1;

                    Tr->T(0,0) = cos(Tr->p1*M_PI/180);  Tr->T(0,1) = sin(Tr->p1*M_PI/180); Tr->T(0,2) = 0;
                    Tr->T(1,0) = -sin(Tr->p1*M_PI/180); Tr->T(1,1) = cos(Tr->p1*M_PI/180); Tr->T(1,2) = 0;
                    Tr->T(2,0) = 0;       Tr->T(2,1) = 0;   Tr->T(2,2) = 1;
                break;
                case ttScale:
                    file >> Tr->p1 >> Tr->p2;

                    Tr->T(0,0) = Tr->p1; Tr->T(0,1) = 0;      Tr->T(0,2) = 0;
                    Tr->T(1,0) = 0;      Tr->T(1,1) = Tr->p2; Tr->T(1,2) = 0;
                    Tr->T(2,0) = 0;      Tr->T(2,1) = 0;      Tr->T(2,2) = 1;
                break;
                default: break;
            };
            transforms.pushback(*Tr);

        }
        file.close();
    }
}

Loader::~Loader()
{
    LinkedList<Transform>::iterator i = transforms.begin();
    for (;i != transforms.end(); ++i)
        delete &(*i);
}

Matrix<float>& Loader::getTransformMatrix(const int id)
{
    LinkedList<Transform>::iterator it = transforms.begin();
    for (int i = 0;i < id; ++i) ++it;
    return (*it).T;
}

string Loader::getTransformString(TransformType Type)
{
    switch (Type){
       case ttTranslate: return "posunuti";
       case ttRotate: return "otoceni";
       case ttScale: return "skalovani";
       default: return "n/a";
    };
}

Loader::TransformType Loader::getTransformType(string Name)
{
    if (Name == "posunuti")
      return ttTranslate;
    else if (Name == "skalovani")
      return ttScale;
    else if (Name == "otoceni")
      return ttRotate;
    else return ttUnknown;
}
