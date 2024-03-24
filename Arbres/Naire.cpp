#include <iostream>
#include <array>

using element = int;

const int N = 50;

struct tableau
{
	element * T;
	int taille;
};

struct maillon
{
	element val;
	maillon * G;
	maillon * D;
};

tableau init_tab(int taille)
{
	tableau tab;
	tab.T = new element[taille];
	tab.taille=taille;
	return tab;
}

using arbre = maillon *;

arbre init()
{
	arbre A = new maillon;
	A->G = nullptr;
	A->D = nullptr;
	return A;
}

tableau sousTab(tableau tab, int deb, int nbEle)
{
	tableau temp;
	temp=init_tab(nbEle);
	for(int i = 0; i<nbEle; ++i)
	{
		temp.T[i]=tab.T[deb+i];
	}
	
	temp.taille = nbEle;
	
	return temp;
}
	
int position(tableau tab, element e)
{
	for(int i = 0; i<tab.taille; ++i)
	{
		if(tab.T[i]==e) return i;
	}
	
	return 0;
}

void aff_tab(tableau tab)
{
	for(int i =0; i<tab.taille; ++i)
	{
		std::cout<<tab.T[i]<<" ";
	}
}

arbre construction(tableau pre, tableau inf, arbre &A)
{

	A = new maillon;
	A->val = pre.T[0];
	
	//inf gauche
	
	tableau inf_G;
	inf_G = init_tab(inf.taille);
	
	inf_G = sousTab(inf, 0, inf.taille - (inf.taille-position(inf, A->val)));
	
	//pre gauche
	
	tableau pre_G;
	pre_G = init_tab(pre.taille); 
	
	
	pre_G = sousTab(pre,1, inf_G.taille);
	
	//inf droit
		
	tableau inf_D;
	inf_D = init_tab(inf.taille);		
	
	inf_D = sousTab(inf, position(inf, A->val)+1, inf.taille-(position(inf, A->val)+1));
	
	
	//pre droit
	tableau pre_D;
	pre_D = init_tab(pre.taille);
	
	pre_D = sousTab(pre,inf_G.taille+1,inf_D.taille);
	
	if(pre_G.taille!=0)
	{
		construction(pre_G, inf_G, A->G);
	}
		
	if(pre_D.taille!=0)
	{
		std::cout<<std::endl;
		construction(pre_D, inf_D, A->D);
	}
	
	return A;
}

void aff(arbre A)
{
	if(A != nullptr)
	{
		aff(A->G);
				std::cout<<A->val<<" ";

		aff(A->D);
	}
}

int poids(arbre A)
{
	if(A!=nullptr)
	{
		return (poids(A->G) + poids(A->D) + A->val);
	}
	
	return 0;
}

bool equilibre(arbre A)
{
	if(A!=nullptr)
	{
		if(A->G!=A->D and (A->G==nullptr or A->D==nullptr))
		{
			return false;
		}
	
		else
		{
			if(A->G!=nullptr)
			{
				if(poids(A->G)== poids(A->D))
				{
					return true;
				}
				
				else return false;
			}
		}
	}
	
	return true;
}

bool contient(arbre A, int p)
{
	if(A!=nullptr)
	{
		if(A->val==p) return true;
		else 
		{
			if (contient(A->G,p) or (contient(A->D,p))) return true;
			else return false;
		}
	}
	
	else return false;
}

void aff_fils(arbre A)
{
	if(A!=nullptr)
	{
		if(A->G!=nullptr)
			A=A->G;
		while(A->D!=nullptr)
		{
			std::cout<<A->val<<" ";
			A=A->D;
		}
		
		std::cout<<A->val<<" ";
	}
}

int recherche_max(arbre A)
{
	if(A!=nullptr)
	{
		if(A->D!=nullptr)
		{
			return recherche_max(A->D);
		}
		
		else return A->val;
	}
	
	return 0;
}

int recherche_min(arbre A)
{
	if(A!=nullptr)
	{
		if(A->G!=nullptr)
		{
			return recherche_min(A->G);
		}
		
		else return A->val;
	}
	
	return 0;
}

bool PlusPetitDomaine(arbre A, arbre B)
{
	if(A!=nullptr)
	{	
		if(recherche_max(A) <= recherche_max(B))
		{
			std::cout<<"ok";
			if(recherche_min(A) >= recherche_min(B))
			{
				std::cout<<"okay";

				return true;
			}
		}
	}
	
	return false;
}



int main()
{
	arbre A;
	arbre B;
	A=init();
	B=init();
	
	//element a [] {16,9,6,4,4,14,13,12,12};
	element a [] {12,3,6,5,17,16,20,19,28};
	element b [] {3,5,6,12,16,17,19,20,28};
	//element b [] {4,6,4,9,14,16,12,13,12};
	
	tableau pre;
	pre=init_tab(9);
	pre.T=a;
	
	tableau inf;
	inf=init_tab(9);	
	inf.T=b;

	construction(pre,inf,A);
	
	element c [] {12,2,6,5,17,16,20,19,29};
	element d [] {2,5,6,12,16,17,19,20,29};
	
	inf.T=c;
	pre.T=d;

	construction(pre,inf,B);
	//std::cout<<A->G->val;
	std::cout<<"Arbre : ";aff(B);
		std::cout<<recherche_min(B)<<"/"<<recherche_min(A);
	std::cout<<PlusPetitDomaine(A,B);
	
	/*std::cout<<"Poids arbre = "<<poids(A);
	
	if(equilibre(A)==true)
	{
		std::cout<<std::endl<<"C'est un arbre equilibre.";
	}
	
	else std::cout<<std::endl<<"Ce n'est pas un arbre equilibre";
	
	if(contient(A,12)==true)
	{
		std::cout<<std::endl<<"Le poid est dans l'arbre";
	}
	
	else std::cout<<std::endl<<"Le poids n'est pas dans l'arbre";*/
	
	
	return 0;
}