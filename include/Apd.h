#ifndef APD_H
#define APD_H
#include <fstream>
#include <iostream>
#include <stack>
#include <cstring>
using namespace std;

class Apd
{
    public:
        Apd(char *numefisier);
        bool VerificareCuvant(char *cuv);
        ~Apd();
    private:
        int NrStari;
        int NrStariFin;
        int StareaInit;
        int *StariFin;
        int NrLit;
        char *Lit;
        int NrTran;
        typedef struct
        {
            char Bagat;
            char Gasit;
            int NrPastrate;
            char SePastreaza[10];
            int Starea1,Starea2; //Din ce stare in ce stare e
        }AlfStiva;
        AlfStiva S[100];

};

#endif // APD_H
