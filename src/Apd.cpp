#include "Apd.h"

Apd::Apd(char *numefisier)
{
    ifstream f(numefisier);
    f>>NrStari>>NrStariFin;
    f>>StareaInit;
    StariFin=new int[NrStariFin];
    for(int i=0;i<NrStariFin;i++)
        f>>StariFin[i];
    f>>NrLit;
    Lit=new char[NrLit];
    for(int i=0;i<NrLit;i++)
        f>>Lit[i];
    f>>NrTran;
    for(int i=0;i<NrTran;i++)
       {
           f>>S[i].Bagat>>S[i].Gasit;
           f>>S[i].NrPastrate;
           for(int j=0;j<S[i].NrPastrate;j++)
           {
              f>>S[i].SePastreaza[j];
           }
           f>>S[i].Starea1>>S[i].Starea2;
       }
}
void showstack(stack <char> s)
{
    while (!s.empty())
    {
        cout << '\t' << s.top();
        s.pop();
    }
    cout << '\n';
}

bool Apd::VerificareCuvant(char *cuv)
{
   int ok=0;
   for(int i=0;i<strlen(cuv);i++)
   {
       ok=0;
       for(int j=0;j<NrLit;j++)
       {
           if(cuv[i]==Lit[j])
           {
               ok=1;
               break;
           }
       }
       if(ok==0)
       {
           cout<<"Cuvant Neacceptat";
           return false;
       }
   }
   typedef struct
   {
       stack <char> Sti;
       int Starea;
       bool Buna;
       char Cuv[100];
   }Stiva;
   Stiva s[60],sf[30];
   for(int i=0;i<60;i++)
   {
       s[i].Sti.push('Z');
       s[i].Starea=StareaInit;
       s[i].Buna=true;
   }
   int NrStive=1;
   int PozCuv=0,Poz[30],l=0,NrSf=0,PozCop[30],O=0;
   while(PozCuv<strlen(cuv))
   {

       NrSf=0;
       /*cout<<NrStive<<" \n";
       for(int i=0;i<NrStive;i++)
       {
           showstack(s[i].Sti);
       }
       cout<<"...\n";*/
       for(int i=0;i<NrStive;i++)
       {
           l=0;
           if(s[i].Buna==true)
           {
              for(int j=0;j<NrTran;j++)
               {
                 if(((cuv[PozCuv]==S[j].Bagat)||(S[j].Bagat=='e'))&&(s[i].Sti.top()==S[j].Gasit)&&(s[i].Starea==S[j].Starea1))
                   {
                      Poz[l]=j;
                      l++;

                   }
               }
           }
           if(l==0)
           {
               s[i].Buna==false;
           }
          else
          {
          for(int k=NrSf;k<NrSf+l-1;k++)
           {
               sf[k]=s[i]; //egalam structurile
               if(S[Poz[k-NrSf]].Bagat!='e')
               sf[k].Cuv[PozCuv]=cuv[PozCuv];
               sf[k].Starea=S[Poz[k-NrSf]].Starea2;
               ok=0;
               for(int j=S[Poz[k-NrSf]].NrPastrate-1;j>=0;j--)
               {
                   if(S[Poz[k-NrSf]].SePastreaza[j]=='e')
                   sf[k].Sti.pop();
                   else
                   {
                       if(ok==0)
                       sf[k].Sti.pop();
                       sf[k].Sti.push(S[Poz[k-NrSf]].SePastreaza[j]);
                       ok=1;
                   }

               }


           }
           if(S[Poz[NrSf+l-1]].Bagat!='e')
           s[i].Cuv[PozCuv]=cuv[PozCuv];
           s[i].Starea=S[Poz[NrSf+l-1]].Starea2;
           ok=0;
            for(int j=S[Poz[NrSf+l-1]].NrPastrate-1;j>=0;j--)
               {
                   if(S[Poz[NrSf+l-1]].SePastreaza[j]=='e')
                    s[i].Sti.pop();
                   else
                   {
                       if(ok==0)
                       s[i].Sti.pop();
                       s[i].Sti.push(S[Poz[NrSf+l-1]].SePastreaza[j]);
                       ok=1;
                   }
               }
           // cout<<NrSf;
           NrSf=NrSf+l-1;
         //  cout<<NrSf;
           }
       }
       //cout<<NrStive+NrSf;
       for(int i=0;i<NrStive+NrSf;i++)
       {
         if((s[i].Sti.empty())&&(PozCuv<strlen(cuv)))
            {

                s[i].Buna=false;
            }
       }
       for(int i=NrStive;i<NrStive+NrSf;i++)
        {
            s[i]=sf[i-NrStive];
            //showstack(s[i].Sti);
        }

       NrStive=NrStive+NrSf;
       PozCuv++;


   }

    for(int i=0;i<NrStive;i++)
       {

           for(int w=0;w<NrTran;w++)
            {
                if((s[i].Starea==S[w].Starea1)&&(S[w].Gasit==s[i].Sti.top())&&(S[w].Bagat=='e')&&(S[w].SePastreaza[0]=='e'))
                {

                    s[i].Sti.pop();
                    s[i].Starea=S[w].Starea2;
                    int g=0;
                    for(int j=0;j<NrStariFin;j++)
                    {
                        if(s[i].Starea==StariFin[j])
                            g=1;
                    }
                    if(g==0)
                        w=0;
                }
            }

         for(int j=0;j<NrStariFin;j++)
        {
            cout<<s[i].Cuv<<" "<<s[i].Buna<<" "<<s[i].Starea<<" "<<i;
            showstack(s[i].Sti);

           if((s[i].Buna==true)&&(s[i].Starea==StariFin[j])&&(strlen(s[i].Cuv)==strlen(cuv)))
           {
               cout<<"Cuvant Acceptat";
               return true;
           }
         }
       }
   cout<<"Cuvant Neacceptat";
   return false;

}
Apd::~Apd()
{
    //dtor
}
