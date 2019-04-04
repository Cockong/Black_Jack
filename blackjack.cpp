#include <iostream>
#include <stdlib.h>
#include<string.h>
#include<time.h>
#include <stdio.h>
#include <iomanip>

using namespace std;

struct main
{
    int numero;
    double total[2];
    double carte[10];
    double victory ;
    double reste ;
    double mise;
    double argent ;
    bool duo;

};


struct jeu
{
    double pigeon;
    double reste;
    double carte[10];
    double proba[10] ;
    main joueur[15] ;
    main croupier;

};

int maxi(double T[10])
{
    int i,m;
    m=T[0];
    for (i=1;i<10;i++)
    {
        if (m<T[i])
        {
            m=T[i];
        }
    }

    return m;
}

int mini(double T[10])
{
    int i,m;
    m=T[0];
    for (i=1;i<10;i++)
    {
        if (m>T[i])
        {
            m=T[i];
        }
    }

    return m;
}

void initab(double T[10])
{
    int i;
    for(i=0;i<10;i++)
    {
        T[i]=0 ;
    }
}


void affichemain(main M)
{
    int i ;
    if (M.numero==100)
    {
        cout << "croupier" << endl ;
    }
    else
    {
        cout << "joueur " << M.numero+1 << endl  ;
    }

    cout << "cartes : " << M.reste << endl ;
    cout << "victoire ? " << M.victory << endl ;
    cout << "total des cartes :" << M.total[0] << "/" << M.total[1] << endl ;
    cout << "argent restant : "<< M.argent << endl ;
    cout << "Mise : "<< M.mise << endl ;

      /*  for (i=0;i<10;i++)
        {
           cout <<M.carte[i] ;

           if (M.carte[i]<10)
        {
            cout <<"      " ;
        }
        else
        {
            cout <<"     " ;
        }
        } */
    cout << endl << endl ;

}

void affichejeu (jeu J)
{
    int i,k;

    cout << "cartes restantes du paquet : " << J.reste << endl ;
    cout << "nombre de joueurs : " << J.pigeon << endl ;

    for (i=1;i<11;i++)
    {
      cout << i <<"      " ;

    }
    cout << endl ;

    for (i=0;i<10;i++)
    {
        if (J.carte[i]<10)
        {
            cout << J.carte[i] <<"      " ;
        }
        else
        {
            cout << J.carte[i] <<"     " ;
        }


    }
    cout << endl ;
    for (i=0;i<10;i++)
    {


        printf("%.2f",J.proba[i]) ;
        if (J.proba[i]<10)
        {
            cout <<"   " ;
        }
        else
        {
            cout <<"  " ;
        }


    }
    cout << endl << endl ;

    for (i=0;i<J.pigeon;i++)
    {
        affichemain(J.joueur[i]) ;

    }

    affichemain(J.croupier) ;
}



int alea(jeu J)
{
    int c,x,i ;
    c=0;
    bool bill ;
    bill=false ;
    int cuMul[10];

    cuMul[0]=J.carte[0] ;
    for (i=1;i<10;i++)
    {
        cuMul[i]=cuMul[i-1]+J.carte[i] ;
    }


    i=J.reste ;
    x=rand()%(i)+1 ;

    i=0 ;
    while ((i<10)&&(bill==false))
    {
        if (x<=cuMul[i])
        {
            c=i+1 ;
            bill=true ;

        }
        i=i+1 ;
    }
    return c ;


}



void issuemain(main &M)
{
    int i;
    for (i=0;i<2;i++)
    {
        if ((M.total[i]==21)&&(M.reste==2))
    {
        cout << "Blackjack !"<< endl ;
        M.victory=1;
    }
    }
    if (min(M.total[0],M.total[1])>21)
            {
                cout <<"burn to hell motherfucker !!"<< endl ;
                M.victory =2;
            }
}

int tirer(jeu &J,main &M)
{

    int c,i;
    c=alea(J) ;
    J.reste-- ;
    J.carte[c-1]--;
    for (i=0;i<10;i++)
    {
      J.proba[i]=100*J.carte[i]/J.reste;

    }

    M.carte[c-1]++ ;
    M.reste++ ;
    M.total[0] =M.total[0]+c ;
    if ((c==1)&&(M.carte[1]+11<21))
    {
        M.total[1] =M.total[1]+11 ;

    }
    else
    {
        M.total[1] =M.total[1]+c ;
    }

    issuemain(M) ;



}

main inimain(jeu &J, int n)
{
    int i;
    main M;
    M.reste=0 ;
    M.victory=0 ;
    M.total[0]=0;
    M.total[1]=0 ;
    M.duo=false ;
    initab(M.carte) ;

        for (i=0;i<n;i++)
        {
           tirer(J, M);
        }


    if (n==2)
    {
        cin >> M.mise ;
        cout <<  endl;
    }
    return M ;
}

void inipartie(jeu &J)
{
    int i;
    double k;
    for (i=0;i<J.pigeon;i++)
    {
        cout << "mise du joueur ? " << i+1 << " " ;
        k=J.joueur[i].argent ;
        J.joueur[i]=inimain(J,2) ;
        J.joueur[i].argent=k ;

    }
    for (i=0;i<10;i++)
    {
        J.joueur[i].numero=i;
        J.joueur[i].duo=false;
    }

    k=J.croupier.argent ;
    J.croupier=inimain(J,1) ;
    J.croupier.numero=100;
    J.croupier.argent=k ;

}

jeu inijeu()
{
    int i,k,c;
    jeu J;

    cout << "nombre de jeux de cartes ? "  ;
    cin >> i ;

    J.reste = i*52 ;

    cout << "nombre de cartes : " << J.reste << endl ;

    for (i=0;i<9;i++)
    {
      J.carte[i]=J.reste/13;

    }
    J.carte[9]=4*J.reste/13;
    for (i=0;i<10;i++)
    {
      J.proba[i]=100*J.carte[i]/J.reste;

    }

    cout << "nombre de pigeons ? " ;
    cin >> J.pigeon ;

    inipartie (J) ;

    for (i=0;i<J.pigeon;i++)
    {
        cout << "argent de depart du joueur " << i+1 << " " ;
        cin >> J.joueur[i].argent ;
        cout << endl ;

    }

    cout << "argent de depart du croupier " ;
    cin >> J.croupier.argent ;




    return J;
}

void split(jeu &J,main &M, int k)
{
    M.carte[k]=1;
    M.argent=M.argent;
    M.reste=1;
    M.total[0]=M.total[0]/2 ;
    M.total[1]=M.total[1]/2 ;
    J.joueur[10-M.numero]=M ;
    M.duo=true ;



}

void jouer(jeu &J,main &M)
{
    int l;
    l=10-M.numero ;
    int n,i,k;
    n=2 ;
    affichemain(M) ;

    while (((n==2)||(n==4))&&(M.victory==0))
           {
               cout << "1 = stand ; " << "2 = tirer ; " ;
    if (M.reste==2)
    {
       cout << "3 = doubler ; " ;
       for (i=0;i<10;i++)
    {
        if ((M.carte[i]==2)&&(M.duo==false)&&(J.joueur[l].duo==false)&&(M.argent>=2*M.mise))
        {
            cout << "4 = split ; " ;
            k=i;

        }

    }

    }

    cin >> n;

    if (n==2)
    {
        tirer(J,M);

    }
    else if (n==3)
    {
        M.mise=M.mise*2 ;
        tirer(J,M);

    }
    else if (n==4)
    {
        split(J,M,k) ;
    }
    affichemain(M) ;

           }


}

void banque(jeu &J, main &M)
{

        while ((max(M.total[0],M.total[1])<17))
        {
            tirer(J,M) ;
        }
        if (max(M.total[0],M.total[1])>21)
        {
            while((min(M.total[0],M.total[1])<17)&&(M.victory!=2))
            {
                tirer(J,M) ;
            }

        }

}

double gain(jeu J,int i)
{
    double g;
    if (J.joueur[i].victory==2)
        {
            cout << "joueur " << i+1 << " lose" <<endl ;
            g=-J.joueur[i].mise ;

        }
         else if (J.joueur[i].victory==1)
         {
             cout << "joueur " << i+1 << " win" <<endl ;
             if (J.croupier.victory==1)
             {
                 g=0.5*J.joueur[i].mise ;
             }
             else
             {
                 g=2*J.joueur[i].mise ;
             }
         }

        if (J.joueur[i].victory==0)
        {
            if (J.croupier.victory==2)
        {
            cout << "joueur " << i+1 << " win" <<endl ;
            g=J.joueur[i].mise ;

        }
        else if (J.croupier.victory==1)
         {
             cout << "joueur " << i+1 << " lose" <<endl ;
             g=-J.joueur[i].mise ;
         }
            else if(J.croupier.victory==0)
            {
                if ((max(J.joueur[i].total[0],J.joueur[i].total[1])<J.croupier.total[0])
                    ||(max(J.joueur[i].total[0],J.joueur[i].total[1])<J.croupier.total[1]))
                {
                    cout << "joueur " << i+1 << " lose" <<endl ;
                    g=-J.joueur[i].mise ;
                }
               else if ((max(J.croupier.total[0],J.croupier.total[1])<J.joueur[i].total[0])
                        ||(max(J.croupier.total[0],J.croupier.total[1])<J.joueur[i].total[1]))
               {
                   cout << "joueur " << i+1 << " win" <<endl ;
                   g=J.joueur[i].mise ;
               }
               else
               {
                   cout << "joueur " << i+1 << " doesn't win but doesn't lose" <<endl ;
                   g=0 ;
               }
        }
    }
    return g ;
}

void issue(jeu &J)
{
    int i,l;
    double g;
    for (i=0;i<J.pigeon;i++)
    {
        if (J.joueur[i].duo==true)
        {
            l=10-i;
            g=gain(J,l) ;

            J.joueur[i].argent=J.joueur[i].argent+g ;
        J.croupier.argent=J.croupier.argent-g ;
        cout << " gain = " << g << endl ;



        }

        g=gain(J,i) ;

            J.joueur[i].argent=J.joueur[i].argent+g ;
        J.croupier.argent=J.croupier.argent-g ;
        cout << " gain = " << g << endl ;



    }


}




int main()
{
    int n=0;
    int i,j;
    srand(time(NULL)) ;
    jeu black ;
    black = inijeu();
    affichejeu(black);
    for (i=0;i<black.pigeon;i++)
    {

        j=10-i;
        jouer(black,black.joueur[i]);
        if (black.joueur[i].duo==true)
        {
           jouer(black,black.joueur[j]);
        }
    }
    banque(black,black.croupier) ;

    issue(black) ;
    affichejeu(black);

    cout << "play again ? if yes press 0" << endl ;
    cin >> n;

    while (n==0)
    {
        inipartie(black) ;
        affichejeu(black);
        for (i=0;i<black.pigeon;i++)
    {

        j=10-i;
        jouer(black,black.joueur[i]);
        if (black.joueur[i].duo==true)
        {
           jouer(black,black.joueur[j]);
        }
    }
    banque(black,black.croupier) ;

    issue(black) ;
    affichejeu(black);

    cout << "play again ? if yes press 0" << endl ;
    cin >> n;

    }



     return 0;

}


