#include "loader.h"

// Stará se o načítání datového souboru
bool Loader::load(const char* szFile,int ScalingFactor)
{
    ifstream file;
    file.open(szFile);

    if (file.is_open()){
        // Prvně přidej počáteční polohu (jako identickou transformaci)
        Transform *Tr = new Transform;
        Tr->type = ttIdentity;
        Tr->T.identity();
        Tr->p1 = Tr->p2 = 0;
        transforms.pushback(*Tr);

        setlocale(LC_NUMERIC,"C"); // Nutné nastavit locale kvůli atof, který jinak nebere . jako desetinnou čárku

        // Dále čti soubor dokud to jde...
        string cmd,p1,p2;
        while(file.good()){
            cmd.clear(); p1.clear(); p2.clear();
            file >> cmd;

            // Zjisti typ transformace
            TransformType tt = getTransformType(cmd);
            if (tt == ttUnknown) continue; // Když nejde zjistit, preskoč

            Transform *Tr = new Transform;
            Tr->type = tt;

            switch (tt) {
                case ttTranslate: // TRANSLACE
                    file >> p1 >> p2;
                    Tr->p1 = ::atof(p1.c_str()); // Lepší použít atof než přímo číst double přes >> protože v případě chyby nastaví failbit
                    Tr->p2 = ::atof(p2.c_str()); // a stream už není good() takže čtení zbytečně skončí ačkoliv další řádky můžou být už v pořádku.

                    Tr->T(0,0) = 1; Tr->T(0,1) = 0; Tr->T(0,2) = Tr->p1*ScalingFactor;
                    Tr->T(1,0) = 0; Tr->T(1,1) = 1; Tr->T(1,2) = -Tr->p2*ScalingFactor; // Zde je mínus kvůli odlišné bázi
                    Tr->T(2,0) = 0; Tr->T(2,1) = 0; Tr->T(2,2) = 1;
                break;
                case ttRotate:    // ROTACE
                    file >> p1;
                    Tr->p1 = ::atof(p1.c_str());

                    Tr->T(0,0) = cos(Tr->p1*M_PI/180);  Tr->T(0,1) = sin(Tr->p1*M_PI/180); Tr->T(0,2) = 0;
                    Tr->T(1,0) = -sin(Tr->p1*M_PI/180); Tr->T(1,1) = cos(Tr->p1*M_PI/180); Tr->T(1,2) = 0;
                    Tr->T(2,0) = 0;       Tr->T(2,1) = 0;   Tr->T(2,2) = 1;
                break;
                case ttScale:   // ŠKÁLOVÁNÍ
                    file >> p1 >> p2;
                    Tr->p1 = ::atof(p1.c_str());
                    Tr->p2 = ::atof(p2.c_str());

                    Tr->T(0,0) = Tr->p1; Tr->T(0,1) = 0;      Tr->T(0,2) = 0;
                    Tr->T(1,0) = 0;      Tr->T(1,1) = Tr->p2; Tr->T(1,2) = 0;
                    Tr->T(2,0) = 0;      Tr->T(2,1) = 0;      Tr->T(2,2) = 1;
                break;
                default: break;
            };
            transforms.pushback(*Tr); // Přidej transformaci do seznamu

        }
        setlocale(LC_NUMERIC,""); // Vrať zpátky původní locale
        file.close(); // Zavři stream po skončení čtení
        return true;
    }
    return false;
}

Loader::~Loader()
{
    // Smaž všechny dynamicky alokované položky v seznamu
    LinkedList<Transform>::iterator i = transforms.begin();
    for (;i != transforms.end(); ++i)
        delete &(*i);
}

// Statická metoda vrátí řetězec s názvem transformace
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

// Statická metoda vrátí položku s typem transformace
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
