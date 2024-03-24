#include <iostream>

using element = int;

struct file
{
	int taillemax;
	int tete;
	int queue;
	element * T;
};

file * creer_file(int taille)
{
	file * F = new file;
	F->taillemax=taille+1;
	F->tete=0;
	F->queue=taille;
	F->T = new element[taille+1];
	return F;
}

bool est_plein(file *F)
{
	return F->tete == (F->queue+2)%F->taillemax;
}

bool est_vide(file *F)
{
	return F->tete == (F->queue+1)%F->taillemax;
}

void ajoute(file * F, element e)
{
	if(est_plein(F)==false)
	{
		F->queue = (F->queue + 1)%F->taillemax;
		F->T[F->queue]=e;
	}
}

element retire(file *F)
{
	if(est_vide(F)==false)
	{
		int som = F->T[F->tete];
		F->tete = (F->tete + 1)%F->taillemax;
		return som;
	}
	
	return 0;
}

void aff(file *F)
{
	if(F->tete<=F->queue)
	{
		for(int i = F->tete; i<=F->queue; ++i)
		{
			std::cout<<F->T[i]<<" ";
		}
	}
	
	else
	{
		if(est_vide(F)==false)
		{
		for(int i = F->tete; i<F->taillemax; ++i)
		{
			std::cout<<F->T[i]<<" ";
		}
		
		for(int i = 0; i<=F->queue; ++i)
		{
			std::cout<<F->T[i]<<" ";
		}
		}
	}
	
	std::cout<<std::endl;
}

int main()
{
	file *F;
	F=creer_file(5);
	ajoute(F,1);
	ajoute(F,2);
	ajoute(F,3);
	ajoute(F,2);
	ajoute(F,3);
	aff(F);
	retire(F);
	retire(F);
	aff(F);
	ajoute(F,6);
	ajoute(F,7);
	aff(F);
	return 0;
}