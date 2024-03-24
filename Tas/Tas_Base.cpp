#include <iostream>
#include <string>

using element = int;

struct alveole
{
	element val;
	bool EstOccupe;
	int suiv;
};

struct TabHachage
{
	alveole * T;
	int m;
	int PosLibre;
};

void init(TabHachage &H, int taille, int reserve)
{
	H.T = new alveole[taille+reserve];
	H.m = taille;
	H.PosLibre = m+r-1;
	
	for(int i = 0; i<H.PosLibre; ++i)
	{
		H.T[i].EstOccupe = false;
		H.T[i].suiv = -1;
	}
}

int h(element e, int taille)
{
	return e%taille;
}

void ajout(element e, TabHachage &H)
{
	int i = h(e,H.m);
	
	if(H.T[i].EstOccupe)
	{
		while(H.T[i].suiv >=0)
			i=H.T[i].suiv;
		
		H.T[i].suiv = H.PosLibre;
	}
}

int main()
{
	TabHachage H;
	
	init(H,11,0);
	ajout(10,H);
	return 0;
}