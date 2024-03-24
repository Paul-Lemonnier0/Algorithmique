#include <iostream>

using element = char;

struct maillon
{
	element val;
	maillon * suiv;
};

using ListeCirc = maillon *;

void init(ListeCirc &L)
{
	L=nullptr;
}

bool est_vide(ListeCirc M)
{
	if(M==nullptr) return true;
	else return false;
}

void ajoute_fin(element e,ListeCirc &M)
{
	ListeCirc p = new maillon;
	p->val=e;
		
	if(est_vide(M))
	{
		p->suiv=p;
		M=p;

	}
	else 
	{
		p->suiv=M->suiv;
		M->suiv=p;
		M=p;
	}
}

void aff(ListeCirc M)
{
	if(M!=nullptr)
	{
		ListeCirc p;
		p=M;
		do{
			p=p->suiv;
			std::cout<<p->val<<" ";
		}
		
		while(p!=M);
	}
	
	else std::cout<<"vide";
}

int long_ite(ListeCirc M)
{
	if(M!=nullptr)
	{
		int i=0;
		ListeCirc p;
		p=M;
		do{
			p=p->suiv;
			++i;
		}
		
		while(p!=M);
		
		return i;
	}
	
	else return 0;
}

int longueur(ListeCirc M, ListeCirc p)
{
	if(p==M) return 1;
	else return 1+ longueur(M,p->suiv);
}

int long_recur(ListeCirc M)
{
	if(M==nullptr)
	{
		return 0;
	}
	
	else return longueur(M,M->suiv);
}

element premier (ListeCirc M)
{
	if(est_vide(M)==false)
	{
		return M->suiv->val;
	}
	
	else return 0;
}

void retirer(ListeCirc &M)
{
	
	if(est_vide(M)==false)
	{
		if(long_ite(M)>1)
		{
			maillon * supp=M->suiv;
			M->suiv=M->suiv->suiv;
			delete supp;
		}
		else M=nullptr;
	}
}

void vider(ListeCirc &M)
{
	while(est_vide(M)==false)
	{
		retirer(M);
	}
}

int main()
{
	ListeCirc L;
	init(L);
	ListeCirc M;
	init(M);
	
	std::cout<<est_vide(M)<<std::endl;
	
	ajoute_fin('a',M);
	ajoute_fin('b',M);
	ajoute_fin('c',M);
	ajoute_fin('d',M);
	aff(M);

	vider(M);
	
	std::cout<<"Longueur = "<<long_recur(M)<<std::endl;

	return 0;
}