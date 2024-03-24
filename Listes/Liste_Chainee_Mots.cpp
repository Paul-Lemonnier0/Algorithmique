#include <iostream>
#include <string>
#include <array>
#include <fstream>


const int N = 4000;

struct occMot
{
    std::string mot;
    int nbre_occ;
};

struct maillon
{
    occMot val;
    maillon * suiv;
};

using listeMots = maillon *;

struct tabMots{
    std::array<std::string,N> tab;
    int taille;
};

struct occLettre{
    char c;
    int nbre_occ;
};

using tabLettres=std::array<occLettre,26>;

////////////////////////////////////////PARTIE 1///////////////////////////////////// 

void initialise (listeMots &L)
{
    L=nullptr;
}

void ajouteDebut (std::string mot, listeMots &L)
{
    listeMots p;
    p= new maillon;
    p->val.mot=mot;
    p->val.nbre_occ=1;
    p->suiv=L;
    L=p;
}
   
void affiche(listeMots L)
{
    if(L!=nullptr)
    {
        std::cout<<L->val.mot<<"("<<L->val.nbre_occ<<")"<<" ";
        affiche(L->suiv);
    }
}

void ajoutesuite(std::string mot, listeMots &L)
{
    if(L==nullptr) ajouteDebut(mot,L);
    else ajoutesuite(mot,L->suiv);
}
/*
void ajoute(std::string mot, listeMots &L)
{
    int i = 0;
    if(L!=nullptr)
    {
        if((mot[i]>L->val.mot[i]) and (mot[i]<L->suiv->val.mot[i]))
        {
            ajouteDebut(mot,L->suiv);
        }
        
        else if (mot==L->val.mot)
        {
            ++L->val.nbre_occ;
        }
        
        else ajoute(mot,L->suiv);
    }
}*/

void ajoute(std::string mot, listeMots &L)
{
    if(L!=nullptr)
    {
        if(mot<L->val.mot)
        {
            ajouteDebut(mot,L);
        }
        
        else if(mot>L->val.mot)
        {
            ajoute(mot,L->suiv);
        }
        
        else if (mot==L->val.mot)
        {
            ++L->val.nbre_occ;
        }
    }
    
    else ajouteDebut(mot,L);
}

int taille(listeMots L)
{
    if(L!=nullptr)
    {
        return 1 + taille(L->suiv);
    }
    return 0;
}

int nombreMots(listeMots L)
{
    if(L!=nullptr)
    {
        return L->val.nbre_occ + nombreMots(L->suiv);
    }
    return 0;
}

bool estValide(listeMots L)
{
    if(L!=nullptr)
    {
        listeMots p;
        p=L;
        while(p!=nullptr)                   //occurence >1
        {
            if(p->val.nbre_occ<1)
            {
                return false;
            }
            
            else p=p->suiv;
        }
        p=L;
        while(p->suiv!=nullptr)                   //triée ?
        {
            if(p->val.mot>p->suiv->val.mot)
            {
                return false;
            }
            else p=p->suiv;
        }
        p=L;
        while(p->suiv!=nullptr)                   //apparait qu'une fois
        {
            if(p->val.mot==p->suiv->val.mot)
            {
                return false;
            }
            else p=p->suiv;
        }
        
        return true;
    }
    return false;
}

int plusLong(listeMots L)
{
    std::string mot="";
    while(L!=nullptr)
    {
        if(mot.length()<L->val.mot.length())
        {
            mot=L->val.mot;
        }
    L=L->suiv;
    }
    return mot.length();
}

void affichageLongueur(listeMots L, int longueur)
{
    int temp;
    if(L!=nullptr)
    {
        temp=L->val.mot.length();
        if(temp==longueur)
        {
            std::cout<<L->val.mot<<" ";
        }
        affichageLongueur(L->suiv,longueur);
    }
}


void supprime_premier(listeMots &L)
{
    if(L!=nullptr)
    {
        listeMots p = L;
        L=L->suiv;
        delete p;
    }
}

void supprime_pos(listeMots &L, std::string mot)
{
    if(mot==L->val.mot)
    {
        supprime_premier(L);
    }
}


void afficheTriLongueur(listeMots L)
{
    int max = plusLong(L);
    
    for(int i = 0; i<= max; ++i)
    {
        affichageLongueur(L,i);
    }
    
    std::cout<<std::endl;
} 

void saisit(listeMots &L)
{
    std::string mot_temp;
    std::cout<<"saisissez un mot : ";
    std::cin>>mot_temp;
    if(mot_temp!="0")
    {
        ajoute(mot_temp, L);
        saisit(L->suiv);
    }
}

void construit(listeMots &L, std::string nomFichier)
{
    std::ifstream fic(nomFichier);
    std::string mot;
    while (not fic.eof())
    {
        fic >> mot;
        if(!fic.good()) {} // Erreur de lecture
        else // Pas d’erreur
        ajoute(mot,L);
    }
}

void remplit(tabMots &T, listeMots L)
{
    int k=0;
    T.taille=0;
    while(L!=nullptr)
    {
        T.tab[k]=L->val.mot;
        ++k;
        ++T.taille;
        L=L->suiv;
    }
}

void affiche_tab(tabMots &T)
{
    for (int i = 0; i<T.taille;++i)
    {
        std::cout<<T.tab[i]<<" ";
    }
}

tabMots separe(tabMots T, tabMots &temp, int bas, int haut)
{
	int k=0;
    for(int i = bas; i<haut;++i)
    {
        temp.tab[k]=T.tab[i];
		++k;
    }
    temp.taille=k;
    return temp;
}
/*
bool appartient(std::string mot, tabMots T)
{
    tabMots temp;
	int milieu = (T.taille+1)/2;
    std::string mot_temp;
	mot_temp=T.tab[milieu];
	std::cout<<"#############"<<std::endl;

	affiche_tab(T);
	std::cout<<" ("<<T.taille<<")";
	std::cout<<"#############"<<std::endl;
	
    if(T.taille>1)
    {
        if(mot==mot_temp)
        {
			std::cout<<"QUOI???";
            return true;
        }
        
        else if(mot<mot_temp)
        {
			std::cout<<"BAS";
            appartient(mot,separe(T,temp,0,milieu));
        }
        
        else 
		{
			std::cout<<"HAUT";
			appartient(mot,separe(T,temp,milieu,T.taille-1));
		}
    }
	
	
	if(T.taille ==1)
	{
		mot_temp=T.tab[0];
		if(mot==mot_temp)
        {
			std::cout<<"heinnnnnnn?";
            return true;
        }
	}
	
    else return t;
	
	return 1;
}*/

bool appartient(std::string mot, tabMots T)
{
    tabMots temp;
	int milieu = (T.taille+1)/2;
    std::string mot_temp;
	mot_temp=T.tab[milieu];
	
    if(T.taille>1)
    {
        if(mot==mot_temp)
        {
            return true;
        }
        
        else if(mot<mot_temp)
        {
            return appartient(mot,separe(T,temp,0,milieu));
        }
        
        else 
		{
			return appartient(mot,separe(T,temp,milieu,T.taille-1));
		}
    }
	
	
	if(T.taille ==1)
	{
		mot_temp=T.tab[0];
		if(mot==mot_temp)
        {
			std::cout<<"heinnnnnnn?";
            return true;
        }
	}
	
    else return false;
	
	return 0;
}

int main()
{
    listeMots L;
    tabMots T;
    initialise(L);
    /*ajouteDebut("bonjour",L);
    ajoutesuite("paul",L);
    ajoutesuite("zimbabwe",L);
    ajoute("zimbabwe",L);
    affiche(L);
    std::cout<<"taille : "<<nombreMots(L)<<std::endl;
    if(estValide(L)==true)
    {
        std::cout<<"La liste est valide"<<std::endl;
    }
    else std::cout<<"la liste n'est pas valide"<<std::endl;
    
    std::cout<<"longueur du mot le plus long : "<<plusLong(L)<<std::endl;
    
    affichageLongueur(L,4);
    std::cout<<std::endl<<"Tri :"<<std::endl;
    afficheTriLongueur(L);
    std::cout<<"###SAISIR VOS MOTS ('0' pour arreter)###"<<std::endl;
    saisit(L);
    affiche(L);*/
    construit(L,"TP1.txt");
    affiche(L);
    remplit(T,L);
    std::cout<<T.taille;
    affiche_tab(T);
	if(appartient("haduzhdazk",T)==true)
	{
		std::cout<<"appartient";
	}
    else std::cout<<"n'appartient pas";
    return 0;
}
