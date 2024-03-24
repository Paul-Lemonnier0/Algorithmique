#include <iostream>
#include <string>
#include <array>

using element = char;

const int N = 50;

using tab = std::array<element, N>;

struct maillon_pile
{
	element val;
	maillon_pile * suiv;
};

using pile = maillon_pile *;

struct maillon
{
	element val;
	maillon * FilsG;
	maillon * FilsD;
	maillon * Pere;
};

using arbre = maillon *;

arbre init()
{
	arbre A = new maillon;
	A->FilsD = nullptr;
	A->FilsG = nullptr;
	A->Pere = nullptr;
	
	return A;
}

int longueur(std::string s)
{
	return s.length();
}

int position(std::string s, element e)
{
	for(int i = 0; i<longueur(s); ++i)
	{
		if(s[i]==e) return i;
	}
	
	return 0;
}

element caractere(std::string s, int i)
{
	return s[i];
}

std::string sousChaine(std::string s, int deb, int nbCar)
{
	std::string temp="";
	
	for(int i = 0; i<nbCar; ++i)
	{
		temp+=s[deb+i];
	}
		
	return temp;
}

arbre construction(std::string prefixe, std::string infixe, arbre &A)
{

	A = new maillon;
	A->val = prefixe[0];
		
	/*
	std::cout<<prefixe<<std::endl;
	std::cout<<infixe<<std::endl;
	std::cout<<std::endl;	*/
	 
	std::string chaine_inf_G = sousChaine(infixe,0, longueur(infixe)- (longueur(infixe)-position(infixe, A->val)));
	std::string chaine_pre_G = sousChaine(prefixe,1, longueur(chaine_inf_G));
		
	std::string chaine_inf_D = sousChaine(infixe, position(infixe, A->val)+1, longueur(infixe)-(longueur(infixe)-position(infixe, A->val)));
	std::string chaine_pre_D = sousChaine(prefixe,longueur(chaine_inf_D)+1,longueur(prefixe)-longueur(chaine_inf_D)-1);
	
	std::cout<<chaine_pre_G<<std::endl;
	
	std::cout<<chaine_pre_D<<std::endl;
	std::cout<<std::endl;
	
	
	if(chaine_pre_G!="")
	{
		construction(chaine_pre_G, chaine_inf_G, A->FilsG);
	}
		
	if(chaine_pre_D!="")
	{
		construction(chaine_pre_D, chaine_inf_D, A->FilsD);
	}
	
	return A;
}

void aff(arbre A)
{
	if(A != nullptr)
	{

		aff(A->FilsG);
		std::cout<<A->val<<" ";
		aff(A->FilsD);	
	}
}

int construire_tab(arbre A, tab &T, int taille)
{
	if(A != nullptr)
	{
		T[taille] = A->val;
		construire_tab(A->FilsG, T, taille+1);
		construire_tab(A->FilsD, T, taille+1);	
	}
	
	return taille;
}

int nbre_filsG(arbre A)
{
	if(A!=nullptr)
	{
		return nbre_filsG(A->FilsG) + 1;
	}
	
	return 0;
}

int max(int a, int b)
{
	if(a>b)
		return a;
	return b;
}

int hauteur (arbre A)
{
	if(A!=nullptr)
		return max(hauteur(A->FilsG) +1, hauteur(A->FilsD) +1);
	return 0;
}
/*
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
}*/

void aff_beau(arbre A, tab T, int esp)
{
	if(A!=nullptr)
	{
	for(int i = 0; i<esp; ++i)
	{
		std::cout<<"-----";
	}

	for(int i = 0; i<esp; ++i)
	{
		std::cout<<"-----";
	}	
	}
	
	aff_beau(A->FilsG, T, --esp);
	std::cout<<std::endl;
}

void aff_tab(tab T, int taille)
{
	for(int i = 0; i<taille; ++i)
	{
		std::cout<<T[i]<<" ";
	}
}

int main()
{
	arbre A;
	A=init();
	
	tab T;
	
	std::string infixe = "WNODLERUF";
	//std::string infixe = "EFBCGDA";
	//std::string prefixe = "ABEFCDG";
	std::string prefixe = "LDNWOUREF";
	
	A=construction(prefixe, infixe, A);
	aff(A);
	
	std::cout<<std::endl;
	
	construire_tab(A,T,0);
	//aff_beau(A,T,hauteur(A));
	return 0;
}