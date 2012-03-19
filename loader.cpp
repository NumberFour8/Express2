#include "loader.h"

Loader::Loader(const char* szFile,int ScalingFactor) : transforms()
{
    ifstream file;
    file.open(szFile);

    if (file.is_open()){
        // Prvně přidej počáteční polohu (identickou transformaci)
        Transform *Tr = new Transform;
        Tr->type = ttIdentity;
        Tr->T.identity();
        Tr->p1 = Tr->p2 = 0;
        transforms.pushback(*Tr);

        // Dále čti soubor dokud to jde...
        string cmd;
        while(file.good()){
            cmd.clear();
            file >> cmd;

            // Zjisti typ transformace
            TransformType tt = getTransformType(cmd);
            if (tt == ttUnknown) continue; // Když nejde zjistit, preskoč

            Transform *Tr = new Transform;
            Tr->type = tt;

            switch (tt) {
                case ttTranslate: // TRANSLACE
                    file >> Tr->p1 >> Tr->p2;

                    Tr->T(0,0) = 1; Tr->T(0,1) = 0; Tr->T(0,2) = Tr->p1*ScalingFactor;
                    Tr->T(1,0) = 0; Tr->T(1,1) = 1; Tr->T(1,2) = -Tr->p2*ScalingFactor; // Zde je mínus kvůli odlišné bázi
                    Tr->T(2,0) = 0; Tr->T(2,1) = 0; Tr->T(2,2) = 1;
                break;
                case ttRotate:    // ROTACE
                    file >> Tr->p1;

                    Tr->T(0,0) = cos(Tr->p1*M_PI/180);  Tr->T(0,1) = sin(Tr->p1*M_PI/180); Tr->T(0,2) = 0;
                    Tr->T(1,0) = -sin(Tr->p1*M_PI/180); Tr->T(1,1) = cos(Tr->p1*M_PI/180); Tr->T(1,2) = 0;
                    Tr->T(2,0) = 0;       Tr->T(2,1) = 0;   Tr->T(2,2) = 1;
                break;
                case ttScale:   // ŠKÁLOVÁNÍ
                    file >> Tr->p1 >> Tr->p2;

                    Tr->T(0,0) = Tr->p1; Tr->T(0,1) = 0;      Tr->T(0,2) = 0;
                    Tr->T(1,0) = 0;      Tr->T(1,1) = Tr->p2; Tr->T(1,2) = 0;
                    Tr->T(2,0) = 0;      Tr->T(2,1) = 0;      Tr->T(2,2) = 1;
                break;
                default: break;
            };
            transforms.pushback(*Tr); // Přidej transformaci do seznamu

        }
        file.close(); // Zavři stream po skončení čtení
    }
}

Loader::~Loader()
{
    // Smaž všechny dynamicky alokované položky v seznamu
    LinkedList<Transform>::iterator i = transforms.begin();
    for (;i != transforms.end(); ++i)
        delete &(*i);
}

// Vrátí řetězec s názvem transformace
const char* Loader::getTransformString(TransformType Type)
{
    switch (Type){
       case ttTranslate: return "posunuti";
       case ttRotate: return "otoceni";
       case ttScale: return "skalovani";
       case ttIdentity: return "pocatecni poloha";
       default: return "n/a";
    };
}

// Vrátí položku s typem transformace
Loader::TransformType Loader::getTransformType(string Name)
{
    if (Name == "posunuti")
      return ttTranslate;
    else if (Name == "skalovani")
      return ttScale;
    else if (Name == "otoceni")
      return ttRotate;
    else if (Name == "pocatecni poloha")
      return ttIdentity;
    else return ttUnknown;
}
