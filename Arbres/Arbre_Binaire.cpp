#include <iostream>
#include <array>
#include <string>
#include <fstream>

const int N = 50;

using element = std::string;

using tab_string = std::array<std::string, N>;
using tab = std::array<int, N>;

struct noeud{
    element val;
    noeud * D;
    noeud * G;
    noeud * P;
};

using arbreBinaire = noeud *;

void init(arbreBinaire &AB)
{
    AB = nullptr;
}

//PT1

struct arbre{
    int taille;
    int racine;
    tab_string E;
    tab G;
    tab D;
    tab P;
};

void lecture(std::string NomFic, arbre &A)
{
    std::string temp;
    int taille_temp, racine_temp;
    std::ifstream fic(NomFic);
    if(not fic.eof())
    {
        fic>>taille_temp;
        A.taille=taille_temp;
        		
        fic>>racine_temp;
        A.racine=racine_temp;
        
        for(int  i = racine_temp; i<=taille_temp; ++i)
        {
            fic>>A.E[i];
            fic>>A.G[i];
            fic>>A.D[i];
        }
    }
    
    else std::cout<<"Le fichier n'est pas bon.";
}

void aff(arbre A)
{
    for(int i =1; i<=A.taille; ++i)
    {
        std::cout<<A.P[i]<<" ";
    }
    std::cout<<std::endl;
}

void remplit_pere(arbre &A)
{
    A.P[1]=0;
    for(int i = A.racine; i<=A.taille; ++i)
    {
        A.P[A.G[i]]=i;
        A.P[A.D[i]]=i;
    }
}

int profondeur(arbre A, std::string etiquette)
{
    bool stop;
    int i =0,compteur=0;
    while(stop==false)
    {
        ++i;
        if(i>A.taille)
        {
            stop=true;
        }
        
        if(A.E[i]==etiquette)
        {
            stop=true;
        }
    }
    
    while(A.P[i]!=0)
    {
        i=A.P[i];
        ++compteur;
    }
    
    return compteur;
}

void aff_infixe(arbre A)
{
    std::string droit_temp,gauche_temp, pere_temp;
    
    for(int  i = A.racine; i<=A.taille; ++i)
    {
        /*if(A.G[i]==0) gauche_temp = "*";
        else gauche_temp = A.E[A.G[i]];
        
        if(A.D[i]==0) droit_temp = "*";
        else droit_temp = A.E[A.D[i]];
        
        if(A.P[i]==0) pere_temp = "*";
        else pere_temp = A.E[A.P[i]];
        
        std::cout<<A.E[i]<<"/ FilsG : "<<gauche_temp<< "/ FilsD : "
        <<droit_temp<< "/ Pere : "<<pere_temp<<"/ profondeur = "<<profondeur(A,A.E[i])<<std::endl;*/
        
        
    }
}

void aff_inf(arbre A, int index)
{
    if(index<=A.taille)
    {
        if(A.G[index]!=0)
        {
           aff_inf(A,++index);
        }
        
        std::cout<<A.E[index]<<'/'<<A.E[A.D[index]]<<"/"<<A.E[A.G[index]]<<"/"<<A.E[A.P[index]]<<"/"<<profondeur(A,A.E[index])<<std::endl;
        
		if(A.D[index]!=0)
        {
            aff_inf(A,A.D[index]);
        }        
    }
}

//PT2

void ajoute(element e, arbreBinaire &AB)
{
    arbreBinaire p;
    p = new noeud;
    p->val = e;
    p->P = AB;
    p->G=nullptr;
    p->D=nullptr;
    AB=p;
}

void parcoursGauche(arbreBinaire &AB, arbre A, int index)
{
    if(A.G[index]!=0)
    {
        ajoute(A.E[A.G[index]], AB->G);
        parcoursGauche(AB->G,A,index+1);
    }
    
}

void parcoursDroit(arbreBinaire &AB, arbre A, int index)
{
    if(A.D[index]!=0)
    {
        ajoute(A.E[A.D[index]], AB->D);
        parcoursGauche(AB->D,A,index+1);
    }
}

void convertir(arbre &A, arbreBinaire AB)
{
    std::string temp;
    temp=A.E[A.racine];
    ajoute(temp, AB);

    //parcoursGauche(AB->G, A, 1);
    //parcoursDroit(AB->D, A, 1);
}

int main()
{
    arbre A;
    arbreBinaire AB;
    init(AB);
    
    std::string nomfic="arbre.txt";
	//A.taille = 9;
	//A.racine = 1;
	//A.G = {2,5,4,7,0,0,0,0,0}
    lecture(nomfic,A);
	std::cout<<A.E[1];
    remplit_pere(A);
    aff(A);
    std::cout<<"profondeur : "<<profondeur(A,"depot_A")<<std::endl;
    //aff_infixe(A);
    A.E[0]="*";
    aff_inf(A,A.racine);
    std::cout<<std::endl;
    //convertir(A,AB);
    //std::cout<<"val : "<<AB->val;
    return 0;
}