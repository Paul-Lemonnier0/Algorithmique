#include <iostream>
#include <ctime>

const int MaxMessage = 100;
const int MaxCle = 100;

struct message
{
    int * corps;
    int length;
};

struct maillon
{
    maillon * suiv;
    maillon * prec;
    int val;
};

struct cle
{
    maillon * tete;
    int length;
};

struct MaillonChemin
{
    bool val;
    MaillonChemin * suiv;
};

using chemin = MaillonChemin *;

struct noeud
{
    int val;
    noeud * G;
    noeud * D;
};

using MessageChiff = noeud *;

//INIT

message InitMessage(int length)
{
    message temp;
    temp.corps = new int[length];
    temp.length = length;
    
    return temp;
}

cle * InitCle(int length)
{
    cle * C = new cle;
    
    C->tete = nullptr;
    C->length = length;
    
    return C;
}

chemin InitChemin()
{
    chemin C;
    C=nullptr;
    return C;
}

MessageChiff InitMessageChiff()
{
    MessageChiff M = new noeud;
    M = nullptr;
    return M;
}

//PRIMITIVES

void ajouteCle(int e, cle *C)
{
    maillon * M = new maillon;
    M->val = e;
    
    if(C->tete == nullptr)
    {
        M->suiv = M;
        M->prec = M;
        
        C->tete = M;
    }
    
    else
    {
        maillon * temp = C->tete;
        while(temp->suiv!=C->tete)
        {
            temp = temp->suiv;
        }
        
        M->suiv = C->tete;
        C->tete->prec = M;
        M->prec = temp;
        temp->suiv = M;
    }
}

void ajouteChemin_debut(bool e, chemin &C)
{
    MaillonChemin * p = new MaillonChemin;
    p->val = e;
    p->suiv = nullptr;
    C = p;
}

void ajouteChemin(bool e, chemin &C)
{
    if(C==nullptr) ajouteChemin_debut(e,C);
    else ajouteChemin(e,C->suiv);
}

void supprimePremierChemin(chemin &Ch)
{
    chemin p = Ch;
    Ch = Ch->suiv;
    delete p;
}

void supprimeChemin(chemin &Ch)
{
    if(Ch!=nullptr)
    {
        supprimePremierChemin(Ch);
        supprimeChemin(Ch);
    }
}


//ALEATOIRE

message MessAleatoire(int length)
{
    message temp = InitMessage(length);
    for(int i = 0; i <length; ++i)
    {
        temp.corps[i] = rand()%(MaxMessage);
    }
    
    return temp;
}

cle * CleAleatoire(int length)
{
    cle * C = InitCle(length);

    for(int i = 0; i<length; ++i)
    {
        ajouteCle(rand()%(MaxCle), C);
    }
    
    return C;
}


void GenereChemin(int e, chemin &C)
{
    bool Bool_temp;
    
    if(e%2 == 0)
        Bool_temp = false;
    else Bool_temp = true;
    
    if(e>1)
    {
        ajouteChemin(Bool_temp, C);
        GenereChemin(e/2,C);
    }
    
    else if (e==1) ajouteChemin(Bool_temp, C);
    
}

void ajouteMC(int e, MessageChiff &MC)
{
    noeud * p = new noeud;
    p->val = e;
    p->G=nullptr;
    p->D=nullptr;
	MC=p;
}

void ajouteMessageChiff(int e, MessageChiff &MC, chemin &Ch)
{
    
	if(MC!=nullptr)
	{
		if(Ch!=nullptr)
		{
			if(Ch->val == true)
				ajouteMessageChiff(e,MC->D,Ch->suiv);
			else ajouteMessageChiff(e,MC->G,Ch->suiv);

		}
		else ajouteMessageChiff(e,MC->G,Ch);
	}
	else 
	{
		ajouteMC(e,MC);
		supprimeChemin(Ch);
	}
}

bool est_feuille(MessageChiff MC)
{
	return (MC->G == nullptr and MC->D == nullptr);
}

int supprimeMC(MessageChiff &MC)
{
	int e = MC->val;
	delete MC;
	return e;
}

int supprime_noeudMC(chemin &Ch, MessageChiff &MC)
{
	if(MC!=nullptr)
	{
		if(est_feuille(MC))
		{
			return supprimeMC(MC);
		}
		
		if(Ch!=nullptr)
		{
			if(Ch->val == true)
				return supprime_noeudMC(Ch->suiv, MC->D);
			else return supprime_noeudMC(Ch->suiv, MC->D);
		}	
	}
	
	return 0;
}

//AFFICHAGE

void affMessage(message M)
{
    for(int i = 0; i<M.length; ++i)
    {
        std::cout<<M.corps[i]<<" ";
    }
}

void affMC(MessageChiff MC)
{
    if(MC!=nullptr)
    {
        affMC(MC->G);
		std::cout<<MC->val<<" ";
        affMC(MC->D);
    }
}

void affCle(cle * C)
{
    maillon * temp = C->tete;
    while(temp->suiv!=C->tete)
    {
        std::cout<<temp->val<<" ";
        temp = temp->suiv;
    }
    std::cout<<temp->val<<" ";
}

void aff_chemin(chemin C)
{
    if(C!=nullptr)
    {
        if(C->val == true)
            std::cout<<"True ";
        else std::cout<<"False ";
        
        aff_chemin(C->suiv);
    }
}


int main()
{
    srand(time(NULL));

    message M;
    cle * C;
    chemin Ch = InitChemin();
    MessageChiff MC;
    
    M=MessAleatoire(10);
    C=CleAleatoire(10);
    MC = InitMessageChiff();
    
    GenereChemin(8,Ch);
    
    std::cout<<"Message : ";
    affMessage(M);
    std::cout<<std::endl;
    std::cout<<"Cle : ";
    affCle(C);
    std::cout<<std::endl;
    std::cout<<"Chemin : ";
    aff_chemin(Ch);
    
	GenereChemin(1,Ch);
    ajouteMessageChiff(1,MC,Ch);
	
	GenereChemin(2,Ch);
    ajouteMessageChiff(2,MC,Ch);
	
	GenereChemin(3,Ch);
    ajouteMessageChiff(3,MC,Ch);
	
	GenereChemin(4,Ch);
    ajouteMessageChiff(4,MC,Ch);
	
	GenereChemin(5,Ch);
    ajouteMessageChiff(5,MC,Ch);
	
	GenereChemin(6,Ch);
    ajouteMessageChiff(6,MC,Ch);
    
    affMC(MC);
    return 0;
}

