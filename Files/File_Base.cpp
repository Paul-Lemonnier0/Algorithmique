#include <iostream>

using element = int;

struct maillon
{
	element val;
	maillon * suiv;
};

struct file
{
	maillon * tete;
	maillon * queue;
};

file * creer_file()
{
	file * F = new file;
	F->tete=nullptr;
	F->queue=nullptr;
	return F;
}

bool est_vide(file *F)
{
	return F->tete==nullptr;
}

void ajouter(file * F, element e)
{
	maillon * M = new maillon;
	if(est_vide(F))
	{
		M->val = e;
		F->tete=M;
		F->queue=M;
		M->suiv=nullptr;
	}	
	
	else
	{
		M->val = e;
		F->queue->suiv=M;
		F->queue=M;
		M->suiv=nullptr;
	}
}

element retirer(file *F)
{
	int som = F->tete->val;
	maillon * M = F->tete;
	F->tete=F->tete->suiv;
	delete M;
	return som;
}

void aff(file * F)
{
	maillon * temp = F->tete;
	while(temp!=F->queue)
	{
		std::cout<<temp->val<<" ";
		temp=temp->suiv;
	}
	
	std::cout<<temp->val<<" "<<std::endl;
}

int main()
{
	file * F;
	F=creer_file();
	std::cout<<"Est vide : "<<est_vide(F)<<std::endl;
	ajouter(F,1);
	ajouter(F,2);
	ajouter(F,3);
	aff(F);
	retirer(F);
	retirer(F);
	aff(F);
	return 0;
}
