#include "loader.h"

Loader::Loader(const char* szFile) : transforms()
{
    ifstream file(szFile);

    if (file.is_open())
    {
        string cmd;
        while(file.good())
        {
            cmd.clear();
            file >> cmd;

            if (cmd == "posunuti"){
                double x,y;
                file >> x >> y;

                MatrixD t(3,3);
                t(0,0) = 1; t(0,1) = 0; t(0,2) = x;
                t(1,0) = 0; t(1,1) = 1; t(1,2) = y;
                t(2,0) = 0; t(2,1) = 0; t(2,2) = 1;

                transforms.pushback(t);
                continue;
            }
            else if (cmd == "otoceni"){
                double phi;
                file >> phi;

                MatrixD t(3,3);
                t(0,0) = cos(phi);  t(0,1) = sin(phi); t(0,2) = 0;
                t(1,0) = -sin(phi); t(1,1) = cos(phi); t(1,2) = 0;
                t(2,0) = 0;         t(2,1) = 0;        t(2,2) = 1;

                transforms.pushback(t);
                continue;
            }
            else if (cmd == "skalovani"){
                double sx,sy;
                file >> sx >> sy;

                MatrixD t(3,3);
                t(0,0) = sx; t(0,1) = 0;  t(0,2) = 0;
                t(1,0) = 0;  t(1,1) = sy; t(1,2) = 0;
                t(2,0) = 0;  t(2,1) = 0;  t(2,2) = 1;

                transforms.pushback(t);
                continue;
            }

        }
        file.close();
    }
}

