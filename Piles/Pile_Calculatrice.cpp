#include <iostream>
#include <array>
#include <string>
#include <cmath>

using element = float;
const int N =100;

using tab = std::array<std::string, N>;

struct maillon{
    element val;
    maillon * suiv;
};

using pile = maillon *;

pile * creer_pile()
{
    pile * P = new pile;
    *P = nullptr;
    return P;
}

bool est_vide(pile * P)
{
    return *P==nullptr;
}

element consulter_sommet(pile *P)
{
    return (*P)->val;
}

element depiler(pile *P)
{
    element som = (*P)->val;
    maillon * M = *P;
    *P=(*P)->suiv;
    delete M;
    return som;
}

void empiler(element e, pile *P)
{
    maillon * M = new maillon;
    M->val = e;
    M->suiv=*P;
    *P=M;
}

int saisie(tab &T)
{
    std::string c="";
    std::cout<<"saisissez vos valeurs : ('a' pour arreter)"<<std::endl;
    int i=0;
    std::cin>>c;
    while (c!="a")
    {
        T[i]=c;
        std::cin>>c;
        ++i;
    }
    
    return i;
}

bool correct(std::string exp)
{
    int longueur = exp.length();
    int compteur_point = 0;
    for(int i = 0; i<longueur; ++i)
    {
        if(compteur_point>1) return false;
        else if(isdigit(exp[i])==false)
        {
            if(exp[i]!='.') return false;
            else ++compteur_point; 
        }
    }
    
	if(compteur_point>1) return false;
	
    else return true;
}

void lecture(pile *P, tab &T, int longueur, bool &expression_correcte)
{
    float v1,v2;
    std::string tempo;
    
    
    for (int i = 0; i<longueur; ++i)
    {
        if(T[i]=="+")
        {
            v1 = depiler(P);
            v2 = depiler(P);
            
            empiler(v1+v2, P);
        }
        else if(T[i]=="-")
        {
            v1 = depiler(P);
            v2 = depiler(P);
            
            empiler(v2-v1, P);
        }
        else if(T[i]=="*")
        {
            v1 = depiler(P);
            v2 = depiler(P);
            
            empiler(v1*v2, P);
        }
        else if(T[i]=="/")
        {
            v1 = depiler(P);
            v2 = depiler(P);
            
            empiler(v2/v1, P);
        }
        
        else if(T[i]=="^")
        {
            v2 = depiler(P);
            v1 = depiler(P);
            
            empiler(pow(v1,v2), P);
        }
        
        else if(T[i]=="RAC")
        {
            v1 = depiler(P);
            
            if(v1<0) 
            {
                std::cout<<"Erreur !";
                i=1000;
            }
            
            else empiler(sqrt(v1), P);
        }

        else 
        {
            
            if(T[i]=="PI")
            {
                tempo="3.14159";
                float temp=std::stof(tempo);
                empiler(temp,P);
            }
            
            else 
            {
                tempo=T[i];

                if(correct(tempo)==true)
                {
                    float temp=std::stof(tempo);
                    empiler(temp,P);
                }
            
                else
                {
                    std::cout<<"Mauvaise expression !";
					expression_correcte = false;
                    i=1000;
                }
            }
        }
    }
}


int main()
{
    pile *P;
    P=creer_pile();
    tab T;
    int longueur=0;
    
	bool expression_correcte = true;
	
    longueur=saisie(T);
    lecture(P,T,longueur,expression_correcte);
        
    if(expression_correcte==true)
	{
		std::cout<<consulter_sommet(P)<<std::endl;
	}
    return 0; 
}