#include <iostream>

using element = int;

struct maillon
{
	element val; 
	maillon * suiv;
};

using pile = maillon *;

pile * creer_pile()
{
	pile * P = new pile;
	*P=nullptr;
	return P;
}

bool est_vide(pile * P)
{
	return (*P)==nullptr;
}

void empiler(pile * P, element e)
{
	maillon * M = new maillon;
	M->val = e;
	M->suiv=(*P);
	(*P)=M;
}

element depiler(pile * P)
{
	int som = (*P)->val;
	maillon * M = (*P);
	(*P)=(*P)->suiv;
	delete M;
	return som;
}

void aff(pile *P)
{
	maillon * temp = *P;
	while(temp->suiv!=nullptr)
	{
		std::cout<<temp->val;
		temp=temp->suiv;
	}
	
	std::cout<<temp->val<<std::endl;
}

element consulter_sommet(pile * P)
{
	return (*P)->val;
}

int main()
{
	pile * P;
	P = creer_pile();
	empiler(P,2);
	empiler(P,3);
	aff(P);
	aff(P);
	return 0;
}