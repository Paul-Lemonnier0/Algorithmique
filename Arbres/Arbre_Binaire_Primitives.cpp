#include <iostream>
#include <array>

const int N = 100;
using tab = std::array<int, N>;

struct noeud
{
    int val;
    int hauteur;
    noeud * G;
    noeud * D;
};

using arbre = noeud *;

arbre init()
{
    arbre A = new noeud;
    A=nullptr;
    return A;
}

int hauteurNoeud(arbre A)
{
    if(A!=nullptr)
    {
        return A->hauteur;
    }
    
    return -1;
}

void ajoute_debut(arbre &A, int e)
{
    arbre p;
    p = new noeud;
    p->val = e;
    p->D=nullptr;
    p->G=nullptr;
    A=p;
    
}

void ajouter(arbre &A, int e)
{
    if(A!=nullptr)
    {
        if(A->val<e)
        {
            ajouter(A->D,e);
        }
        
        else ajouter(A->G,e);        
    }
    
    else
    {
        ajoute_debut(A,e);
    }
}

arbre generer(tab T, int n)
{
    arbre A;
    A=init();
    
    for(int i = 0; i<n; ++i)
    {
        ajouter(A,T[i]);
    }
    
    return A;
}

void aff(arbre A)
{
    if(A!=nullptr)
    {
        aff(A->G);
        //std::cout<<"Valeur : "<<A->val<<"/ Adresse : "<<A<<"/ Adresse Gauche : "<<A->G<<"/ Adresse Gauche : "<<A->D<<std::endl;
        
        std::cout<<A->val<<" ";
        aff(A->D);
    }
}

bool appartient(arbre A, int e)
{
    if(A!=nullptr)
    {
        if(A->val < e)
        {
            return appartient(A->D,e);
        }
        
        else if(A->val > e)
        {
            return appartient(A->G,e);
        }
        
        else return true;
    }
    
    else return false;
}

bool est_feuille(arbre A)
{
    return (A->G==nullptr and A->D==nullptr);
}

bool UnFils(arbre A)
{
    return ((A->G!=nullptr and A->D==nullptr) or (A->G==nullptr and A->D!=nullptr));
}

int predecesseur(arbre A)
{
    if(A!=nullptr)
    {
        if(A->D==nullptr)
        {
            return A->val;
        }
        else return predecesseur(A->D);
    }
    else return 0;
}


int supprime_noeud(arbre &A)
{
    int valeur;
    
    if(est_feuille(A))
    {
      valeur = A->val;
      delete A;
      A=nullptr;
    }
    
    
    else if(UnFils(A))
    {
        noeud * temp;
        valeur=A->val;
        if(A->G==nullptr)
        {
            A->val=A->D->val;
            temp = A->D;
            A->D = temp->D;
            A->G = temp->G;
        }
        
        else
        {
            A->val=A->G->val;
            temp = A->G;
            A->D = temp->D;
            A->G = temp->G;
        }
        
        delete temp;
    }
    
    return valeur;

}

int supprime(arbre &A, int e)
{
    if(A!=nullptr)
    {
        if(A->val < e)
        {
            return supprime(A->D,e);
        }
        
        else if(A->val > e)
        {
            return supprime(A->G,e);
        }
        
        else 
        {   
            if(est_feuille(A) == false and UnFils(A) == false)
            {
                A->val =  predecesseur(A->G);
                return supprime(A->G,A->val);
            }
            
            else return supprime_noeud(A);
        }
    }
    else return 0;
}

int somme(arbre A,int x)
{
    if(A!=nullptr)
    {

        if(A->val<x)
        {
            return A->val + somme(A->G,x) + somme(A->D,x);
        }
        else 
        {
            return somme(A->G,x);
        }
    }
    else return 0;
}

void fusionner(arbre &a1, arbre a2)
{
    if(a2!=nullptr)
    {
        ajouter(a1,a2->val);
        fusionner(a1,a2->G);
        fusionner(a1,a2->D);
    }
}

int max(int a, int b)
{
    if(a>b) return a;
    else return b;
}

int hauteur(arbre A)
{
    if(A!=nullptr)
    {
        return 1 + max(hauteur(A->G),hauteur(A->D));
    }
    else return 0;
}

void MAJhauteurNoeud(arbre &A)
{
    if(A!=nullptr)
    {
        A->hauteur = hauteur(A)-1;
        MAJhauteurNoeud(A->G);
        MAJhauteurNoeud(A->D);
    }
}

bool equilibre(arbre A)
{
    if(A!=nullptr)
    {
        int height = hauteur(A->G)-hauteur(A->D);
        if(height>=-1 and height<=1)
        {
            bool EstEquilibre = equilibre(A->G);
            if(EstEquilibre == true)
                return equilibre(A->D);


            else return false;
        }
        else return false;
    }
    else return true;
}

void supprimeMemoire(arbre &A)
{
    if(A!=nullptr)
    {
        supprimeMemoire(A->G);
        supprimeMemoire(A->D);
        std::cout<<A->val<<" ";
        supprime_noeud(A);
    }
}

arbre rotationsimpleG(arbre &A)
{
    if(A!=nullptr)
    {
        arbre temp = A->D;
		A->D = A->D->G;
		temp->G = A;
		A=temp;
    }
	
	return A;
}

arbre rotationsimpleD(arbre &A)
{
    if(A!=nullptr)
    {
        arbre temp = A->G;
		A->G = A->G->D;
		temp->D = A;
		A=temp;
    }
	
	return A;
}

void rotationDoubleDG(arbre &A)
{
	if(A!=nullptr)
	{
		A->D = rotationsimpleD(A->D);
		A = rotationsimpleG(A);
	}
}

void rotationDoubleGD(arbre &A)
{
	if(A!=nullptr)
	{
		A->G = rotationsimpleG(A->G);
				
		A = rotationsimpleD(A);	
	}
}

int DiffHauteur(arbre A)
{
	if(A!=nullptr)
	{
		return hauteur(A->D)-hauteur(A->G);
	}
	
	return 0;
}

void reequilibrer(arbre &A)
{
	if(A!=nullptr)
	{
		int height = DiffHauteur(A);
		int temp_height;
		
		if(height == -2)
		{
			temp_height = DiffHauteur(A->G);
			if(temp_height == -1)
				rotationsimpleD(A);
			else if (temp_height == 1) 
				rotationDoubleGD(A);
		}
		
		else if (height == 2)
		{
			temp_height = DiffHauteur(A->D);
			if(temp_height == 1)
				rotationsimpleG(A);
			else if (temp_height == -1)
				rotationDoubleDG(A);
		}
		else if(height<-2)
		{
			reequilibrer(A->G);
			rotationsimpleD(A);
		}
		
		else if (height>2)
		{
			reequilibrer(A->D);
			rotationsimpleG(A);
		}
		
		reequilibrer(A->G);
		reequilibrer(A->D);
	}
}
	
void ajouterAVL(arbre &A, int e)
{
	if(A!=nullptr)
	{
		if(e>A->val)
			ajouterAVL(A->D, e);
		else ajouterAVL(A->G, e);
	}
	
	else ajoute_debut(A,e);
}

void GenereAVL(tab T, arbre &A, int taille)
{
	for(int i = 0; i<taille; ++i)
	{
		ajouterAVL(A,T[i]);
	}
	
	reequilibrer(A);
	MAJhauteurNoeud(A);
}

int main()
{
    arbre A,A2, A3;
    tab T = {5 , 3 , 7 , 1 , 8 , 10 , 9 , 5 , 7 , 7};
    tab T2 = {15 , 10 , 26 , 7 , 9 , 23 , 13 , 26 , 10 , 26 };
    
    tab T3 = {5 , 2 , 4 , 3 , 1 , 9};
    
    
    A=generer(T,10);
    A2=generer(T2,10);
    A3=generer(T3,6);
    aff(A);
    std::cout<<std::endl;

    aff(A2);
    std::cout<<std::endl;
    aff(A3);
    
    std::cout<<std::endl;

    std::cout<<"Somme : "<<somme(A,9)<<std::endl;
        
    std::cout<<std::endl<<equilibre(A3);
        
    MAJhauteurNoeud(A3);

    reequilibrer(A3);
	MAJhauteurNoeud(A3);
	//rotationsimpleG(A);
	//aff(A3);
	ajouterAVL(A3,8);
	MAJhauteurNoeud(A3);

	aff(A3);
	std::cout<<std::endl<<equilibre(A3);
	std::cout<<A3->D->D->G->val;
	
	
    reequilibrer(A3);
	std::cout<<std::endl<<A3->D->G->val;

	std::cout<<std::endl<<equilibre(A3);
	
	std::cout<<"###################################"<<std::endl;
	
	GenereAVL(T,A3,10);
	aff(A3);
	std::cout<<std::endl<<equilibre(A3);

	
    //Rendu a la question 12
    
    return 0;
}
