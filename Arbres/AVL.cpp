#include <iostream>
#include <array>

const int N = 50;

using tab = std::array<int ,N>;
using element = int;

struct noeud
{
	element val;
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

void ajoute_premier(arbre &A, element e)
{
	arbre P = new noeud;
	P->val = e;
	P->G = nullptr;
	P->D = nullptr;
	A=P;
}

void ajouter(arbre &A, element e)
{
	if(A!=nullptr)
	{
		if(e<=A->val)
		{
			ajouter(A->G,e);
		}
		
		else
		{
			ajouter(A->D,e);
		}
	}
	
	else
	{
		ajoute_premier(A,e);
	}
}

arbre genere(tab T, int n)
{
	arbre A = init();
	for(int i = 0; i<n; ++i)
	{
		ajouter(A,T[i]);
	}
	
	return A;
}

element supprime(arbre &A, element e)
{
	return A->val;
}

void aff(arbre A)
{
	if(A!=nullptr)
	{
		aff(A->G);
		std::cout<<A->val<<" ";
		aff(A->D);
	}
}

void rotation_simpleG(arbre &A)
{
	if(A!=nullptr)
	{
		arbre temp = A->D;
		A->D = A->D->G;
		temp->G = A;
		A=temp;
	}
}

void rotation_simpleD(arbre &A)
{
	if(A!=nullptr)
	{
		arbre temp = A->G;
		A->G= A->G->D;
		temp->D = A;
		A=temp;		
	}
}

void rotation_doubleDG(arbre &A)
{
	if(A!=nullptr)
	{
		rotation_simpleD(A->D);
		rotation_simpleG(A);
	}
}

void rotation_doubleGD(arbre &A)
{
	if(A!=nullptr)
	{
		rotation_simpleG(A->G);
		rotation_simpleD(A);
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
	else return -1;
}

int indiceHauteur(arbre A)
{
	if(A!=nullptr)
	{
		return hauteur(A->D)-hauteur(A->G);
	}
	
	else return 0;
}

void equilibre(arbre &A)
{
	if(A!=nullptr)
	{
		equilibre(A->G);
		
		equilibre(A->D);
	}
}

int main()
{
	arbre A;
	A=init();
	
	tab T = {2, 1 , 5 , 4 , 6 , 7};
	A=genere(T,6);
	rotation_simpleG(A);
	aff(A);
	
	//std::cout<<A->D->D->D->val;
	
	return 0;
}

