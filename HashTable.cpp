#include<iostream>
using namespace std;
struct Produs{
	int id;
	float pret;
	char* denumire;
};
struct Nod{
	Produs* infoUtil;
	Nod* next;
};
struct HashTable{
	Nod* *vector;//vector de pointeri la lista
	int nrElemente;
};
Produs* creareInfoUtil(int id, char* denumire, float pret)
{
	Produs* tmp=(Produs*)malloc(sizeof(Produs));
	tmp->id=id;
	tmp->denumire=(char*)malloc(strlen(denumire)+1);
	strcpy(tmp->denumire, denumire);
	tmp->pret=pret;
	return tmp;
}
Nod* creareNod(Produs* infoUtil)
{
	Nod* tmp=NULL;
	tmp=(Nod*)malloc(sizeof(Nod));
	tmp->infoUtil=infoUtil;
	tmp->next=NULL;
	return tmp;
}
int functie_hash(int cheie, int dim)
{
	 return cheie%dim;
}
void initHashTable(HashTable &htab, int nrEl)
{
	htab.nrElemente=nrEl;
	htab.vector=(Nod* *)malloc(sizeof(Nod*)*nrEl);
	memset(htab.vector,0,sizeof(Nod *)*nrEl);

}
//inserare - chaining  
void inserareHashTable(HashTable htab, Nod* nod)
{
	int poz=functie_hash(nod->infoUtil->id, htab.nrElemente);
	if(htab.vector[poz]==NULL)
		htab.vector[poz]=nod;
	else
	{
		Nod* tmp=htab.vector[poz];
		nod->next=tmp;
		tmp=nod;
		htab.vector[poz]=tmp;
	}
}
void parcurgereHashTable(HashTable htab)
{
	if(htab.vector!=NULL)
	{
		for(int i=0;i<htab.nrElemente;i++)
		{
			if(htab.vector[i]!=NULL)
			{
				printf("Lista nr. %d:\n",i); 
				Nod* tmp=htab.vector[i];
				while(tmp!=NULL)
				{
					printf(" %d %s %f\n",tmp->infoUtil->id,tmp->infoUtil->denumire,tmp->infoUtil->pret);
					tmp=tmp->next;
				}
			}
		}
	}
}
void main()
{
	FILE *pfile=fopen("produse.txt","r");
	HashTable htab;
	initHashTable(htab,29);
	if(pfile)
	{
		int id=0;
		char denumire[50];
		float pret=0.0;
		fscanf(pfile,"%d",&id);
		while(!feof(pfile))
		{
			fscanf(pfile,"%s",denumire);
			fscanf(pfile,"%f",&pret);
			Produs* infoUtil=creareInfoUtil(id, denumire, pret);
			Nod* nod=creareNod(infoUtil);
			inserareHashTable(htab, nod);
				
			fscanf(pfile,"%d",&id);
		}
		fclose(pfile);
		parcurgereHashTable(htab);
	}
}
