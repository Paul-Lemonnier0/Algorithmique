#include <iostream>

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
	arbre A;
	A = nullptr;
	return A;
}

void ajouter_debut(arbre &A, element e)
{
	noeud * p = new noeud;
	p->val = e;
	p->G = nullptr;
	p->D = nullptr;
	A=p;
}

void ajouter(arbre &A, element e)
{
	if(A!=nullptr)
	{
		if(e>A->val)
			ajouter(A->D,e);
		else ajouter(A->G, e);
	}
	else ajouter_debut(A,e);
}

bool est_feuille(arbre A)
{
	return (A->G == nullptr and A->D == nullptr);
}

bool UnFils(arbre A)
{
    return ((A->G!=nullptr and A->D==nullptr) or (A->G==nullptr and A->D!=nullptr));
}

void supprimer_premier(arbre &A)
{
	delete A;
	A = nullptr;
}

void supprime_noeud(arbre &A)
{
	if(est_feuille(A))
		supprimer_premier(A);
	else if(UnFils(A))
	{
		noeud * temp;
		if(A->G==nullptr)
		{
			temp = A->D;
			A->val = A->D->val;
			A->D = temp->D;
			A->G = temp->G;
		}
		
		else
		{
			temp = A->G;
			A->val = A->G->val;
			A->D = temp->D;
			A->G = temp->G;
		}
		
		delete temp;
	}
}

int predecesseur(arbre &A)
{
	if(A!=nullptr)
	{
		if(A->D==nullptr)
			return A->val;
		else
			return predecesseur(A->D);
	}
	
	else return 0;
}

void supprimer(arbre &A, element e)
{
	if(A!=nullptr)
	{
		if (e>A->val)
			supprimer(A->D,e);
		else if (e<A->val) supprimer(A->G,e);
		
		else
		{
			if(est_feuille(A) == false and UnFils(A) == false)
			{
				A->val = predecesseur(A->G);
				supprimer(A->G, A->val);
			}
			
			else supprime_noeud(A);

		}
	}
	
	else std::cout<<"Pas trouvé";
}

void affichage(arbre A)
{
	if(A!=nullptr)
	{
		affichage(A->G);
		std::cout<<A->val<<" ";
		affichage(A->D);
	}
}

int main()
{
	arbre A;
	A = init();
	
	ajouter(A,7);
	ajouter(A,4);
	ajouter(A,6);
	ajouter(A,9);
	ajouter(A,2);
	ajouter(A,8);

	
	affichage(A);
	supprimer(A,4);
	std::cout<<std::endl;
	affichage(A);

	return 0;
}