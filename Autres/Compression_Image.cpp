#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <array>

const int NC = 10;
const int NL = 10;


using element = int;
using pixel = int;

using ligne_image = std::array<pixel,NC>;
using image = std::array<ligne_image,NL>;

struct couple
{
	pixel v;
	int n;
};

struct maillon_couple
{
	couple val;
	maillon_couple * suiv;
};

using liste = maillon_couple *;
using image_comp = liste *;
void init (liste &L)
{
	L = nullptr;
}

void ajoute_premier(pixel v,int n, liste &L)
{
	liste p = new maillon_couple;
	p->val.v=v;
	p->val.n=n;
	p->suiv=L;
	L=p;
}

void ajoute_suite(pixel v, int n, liste &L)
{
	if (L==nullptr) ajoute_premier(v,n, L);
	else ajoute_suite(v,n, L->suiv);
}

void supprime_premier(liste &L)
{
	if (L!=nullptr)
	{
		liste p;
		p=L;
		L=L->suiv;
		delete p;
	}
}

void aff(int compteur, liste &L)
{
	if (L!=nullptr)
	{
		compteur+=L->val.n;
		if(compteur<=NC)
		{
		std::cout<<"("<<L->val.v<<";"<<L->val.n<<")";
		aff(compteur,L->suiv);
		}
		
		else 
		{
			std::cout<<std::endl;
			compteur=0;
			std::cout<<"("<<L->val.v<<";"<<L->val.n<<")";
			aff(compteur,L->suiv);
		}
	}
}

void aff_comp(image_comp N)
{
	for (int i = 0; i<NL; ++i)
	{
		aff(0,N[i]);
		std::cout<<std::endl;
	}
}

void random_ligne(int NC, ligne_image &T)
{
	int a=0,e,i;
	srand(time(NULL));
	while (a<NC-1)
	{
		e=rand()%255;
		i=rand()%10;
		if(a+i>=NC-1)
		{
			i=NC-a;
		}
		for(int k=0; k<i; ++k)
		{
			T[a]=e;
			++a;
		}	
	}
}

void random_image(int NL, image &M)
{
	int a=0,b=0,e,i;
	srand(time(NULL));
	while (b<NL)
	{
		if(a<NC-1)
		{
			e=rand()%255;
			i=rand()%4;
			if(a+i>=NC-1)
			{
				i=NC-a;
			}
			for(int k=0; k<i; ++k)
			{
				M[b][a]=e;
				++a;
			}	
		}
		else 
		{
			b=b+1;
			a=0;
		}
	}
}

void aff_img(int NC, int NL, image M)
{
	for (int i = 0; i<NL; ++i)
	{
		for(int j = 0; j<NC; ++j)
		{
			std::cout<<M[i][j]<<" ";
		}
		
		std::cout<<std::endl;
	}
}
/*
void compression(int i, int j, int valeur, image M, liste &L)
{
	if(j<NL)
	{
		if(i<NC)
		{
			if ((i==0) and (j==0))
			{
				ajoute_suite(M[j][i],1,L);
				compression(i+1,j,M[j][i],M,L);
			}
			
			else if(M[j][i]!=valeur)
			{
				ajoute_suite(M[j][i],1,L);
				compression(i+1,j,M[j][i],M,L->suiv);
			}
			
			else 
			{
				L->val.n=L->val.n+1;
				compression(i+1,j,valeur,M,L);
			}
		}
		else 
		{
			i = 0;
			compression(i,j+1,M[j][i],M,L);
		}
	}
}*/

void compression_ligne(int i, int j,int valeur, image M, liste &L)
{
	if(i<NC)
	{
		if (i==0)
		{
			init(L);
			ajoute_suite(M[j][i],1,L);
			compression_ligne(i+1,j,M[j][i],M,L);
		}
			
		else if(M[j][i]!=valeur)
		{
			ajoute_suite(M[j][i],1,L);
			compression_ligne(i+1,j,M[j][i],M,L->suiv);
		}
		
		else 
		{
			L->val.n=L->val.n+1;
			compression_ligne(i+1,j,valeur,M,L);
		}
	}
}


void compression_image(int j,image M,liste &L,image_comp &N)
{	
	while(j<NL)
	{	
		compression_ligne(0,j,0,M,L);
		N[j]=L;
		++j;
	}
}

void decompression_ligne(int compteur,liste L, ligne_image &M)
{

	if (L!=nullptr)
	{
		for (int j = 0; j<L->val.n; ++j)
		{
			M[compteur]=L->val.v;
			++compteur;
		}
			
		if(L->suiv!=nullptr)
		{
			decompression_ligne(compteur,L->suiv,M);
		}
	}
}

void decompression_image(int compteur, image_comp N, image &M,ligne_image ligne)
{
	if(N[compteur]!=nullptr)
	{
		decompression_ligne(0,N[compteur],ligne);
		M[compteur]=ligne;
		decompression_image(compteur+1,N,M,ligne);
	}
}

int main()
{
	//déclarations
	image M,K;
	liste L;
	init(L);
	ligne_image ligne;
	image_comp N;
	N=new liste[NL];
	
	//générations matrice aléatoires
	random_image(NL,M);
	aff_img(NC,NL,M);
	
	//compression 
	compression_image(0,M,L,N);
	aff_comp(N);
	
	//décompression
	decompression_image(0,N,K,ligne);
	aff_img(NC,NL,K);

	return 0;
}

