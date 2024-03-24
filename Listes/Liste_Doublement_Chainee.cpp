#include <iostream>

using element = int;

struct maillon
{
    element val;
    maillon * suiv;
    maillon * prec;
};

struct liste
{
    maillon * tete;
    maillon * queue;
};

liste * init()
{
    liste * L = new liste;
    L->tete=nullptr;
    L->queue=nullptr;
    return L;
}

bool est_vide(liste * L)
{
    return (L->queue==nullptr);
}

void insertTete(element e, liste *L)
{
    maillon * M = new maillon;
    M->val=e;
    M->suiv=L->tete;
    M->prec=nullptr;

    if(est_vide(L)==true)
    {
        L->queue=M;
    }
    
    else L->tete->prec=M;
    
    L->tete=M;
}

void insertQueue(element e, liste *L)
{
    maillon * M = new maillon;
    M->val=e;
    M->prec=L->queue;
    M->suiv=nullptr;

    if(est_vide(L)==true)
    {
        L->tete=M;
    }
    
    else L->queue->suiv=M;
    
    L->queue=M;
}

/*
void aff(liste *L)
{
    if(est_vide(L)==false)
    {
        std::cout<<L->tete->val<<"/"<<L->queue->val<<std::endl;
    }
}*/


void affTete(liste *L)
{
    liste * temp;
    temp=init();
    temp->tete=L->tete;
    
    while(temp->tete!=L->queue)
    {
        std::cout<<temp->tete->val<<" ";
        temp->tete=temp->tete->suiv;
    }
    std::cout<<temp->tete->val<<std::endl;
}

void aff_recursive_Tete(liste *L)
{
        if(L->tete!=L->queue)
        {
            std::cout<<L->tete->val<<" ";
            L->tete=L->tete->suiv;

            aff_recursive_Tete(L);

        }
        
        else 
        {
            std::cout<<L->tete->val<<std::endl;  
            
            while(L->tete->prec!=nullptr)
            {
                L->tete=L->tete->prec;
            }
        }
		std::cout<<std::endl;
}

void affQueue(liste *L)
{
    liste * temp;
    temp=init();
    temp->queue=L->queue;
    
    while(temp->queue!=L->tete)
    {
        std::cout<<temp->queue->val<<" ";
        temp->queue=temp->queue->prec;
    }
    std::cout<<temp->queue->val<<std::endl;
}


int longueur (liste *L)
{
	liste * temp;
	temp=init();
	temp->tete=L->tete;
	int length = 0;
	while(temp->tete!=L->queue)
	{
		++length;
		temp->tete=temp->tete->suiv;
	}
	
	
	return ++length;
}

void suppr_tete(liste *L)
{
    liste * temp;
    temp=init();
    temp->tete=L->tete;
    L->tete=L->tete->suiv;
    delete temp;
}

void suppr_queue(liste *L)
{
    liste * temp;
    temp=init();
    temp->queue=L->queue;
    L->queue=L->queue->prec;
    delete temp;
}

maillon * appartient (liste * L,element e)
{
    liste * temp;
    temp=init();
    temp->tete = L->tete;
    
    while(temp->tete != L->queue)
    {
        if(e==temp->tete->val)
        {
            return temp->tete;
        }
        
        else temp->tete=temp->tete->suiv;
    }
    
   
    if(e==temp->tete->val)
    {
        return temp->tete;
    }
    delete temp;
    return nullptr;
}

maillon * app_recur (liste *L, element e)
{
    if(L->tete!=L->queue)
        {
            if(e==L->tete->val)
            {
                maillon * temp;
                temp=L->tete;
                while(L->tete->prec!=nullptr)
                {
                    L->tete=L->tete->prec;
                }
                return temp;
            }
            
            L->tete=L->tete->suiv;
            return app_recur(L,e);
        }
    else 
    {      
        if(e==L->tete->val)
            {
                maillon * temp;
                temp=L->tete;
                while(L->tete->prec!=nullptr)
                {
                    L->tete=L->tete->prec;
                }
                return temp;
            }
        else
        {
            while(L->tete->prec!=nullptr)
            {
                L->tete=L->tete->prec;
            }
            return nullptr;
        }
    }
    return nullptr;
}

void insert_pos(liste * L, element e, element x)
{
        int test=0;
        while(test==0)
        {
            if(L->tete==L->queue)
            {
                test=1;
            }
            
            else if(L->tete->val==x)
            {
				L->tete=L->tete->suiv;
				maillon * N = new maillon;
				N->val=e;
				
				N->prec=L->tete->prec;
				N->suiv=L->tete;
				
				L->tete->prec->suiv=N;
				L->tete->prec=N;	
				
				L->tete=N;
				
                test=2;
            }
            
            else L->tete=L->tete->suiv;
        }        
        
		if(L->tete==L->queue and L->tete->val == x)
		{
			maillon * N = new maillon;
			N->val=e;
			N->prec=L->queue;
			N->suiv=nullptr;
			L->queue->suiv=N;			
			L->queue=N;
		}
		
        while(L->tete->prec!=nullptr)
        {
            L->tete=L->tete->prec;
        }
}

void insert_pos_arriere(liste * L, element e, element x)
{
        int test=0;
        while(test==0)
        {
            if(L->tete==L->queue)
            {
                test=1;
            }
            
			else if (L->tete->prec==nullptr and L->tete->val==x)
			{
				maillon * N = new maillon;
				N->val=e;
				N->suiv=L->tete;
				N->prec=nullptr;
				
				L->tete->prec=N;

                test=2;
			}
			
            else if(L->tete->val==x)
            {
				maillon * N = new maillon;
				N->val=e;
				N->suiv=L->tete;
				N->prec=L->tete->prec;
				
				L->tete->prec->suiv=N;
				L->tete->prec=N;
                test=2;
            }
            
            else L->tete=L->tete->suiv;
        }        
		
        while(L->tete->prec!=nullptr)
        {
            L->tete=L->tete->prec;
        }
}

int main()
{
    liste * L;
    
    L=init();
    
    insertQueue(1,L);
    insertTete(2,L);
    insertTete(3,L);
    insertQueue(0,L);
	insertQueue(5,L);

    affTete(L);
    insert_pos_arriere(L,7,3);
    affTete(L);

    return 0;
}

