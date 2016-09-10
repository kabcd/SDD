#include<iostream>
using namespace std;
struct Produs{
	int id;
	float pret;
	char* denumire;
};
struct HashTable{
	Produs* *vector;
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
int functie_hash(char* cheie, int dim)
{
	int sum=0;
	for(int i=0;i<strlen(cheie);i++)
		sum+=cheie[i];
	return sum%dim;
}

void initHashTable(HashTable &htab, int nrEl)
{
	htab.nrElemente=nrEl;
	htab.vector=(Produs* *)malloc(sizeof(Produs*)*nrEl);
	memset(htab.vector,0,sizeof(Produs*)*nrEl);
}
//inserare - linear probing
void inserareHashTable(HashTable htab, Produs* info)
{
	int poz=functie_hash(info->denumire, htab.nrElemente);
	if(htab.vector[poz]==NULL)
		htab.vector[poz]=info;
	else
	{
		int ok=0;
		for(int i=poz+1;i<htab.nrElemente && !ok;i++)
		{
			if(htab.vector[i]==NULL)
			{
				htab.vector[i]=info;
				ok=1;
			}
		}
		if(ok==0)
		{
			for(int i=poz-1;i>=0 && !ok;i--)
			{
				if(htab.vector[i]==NULL)
				{
					htab.vector[i]=info;
					ok=1;
				}
			}
		}
	}
}
void parcurgereHashTable(HashTable htab)
{
	if(htab.vector!=NULL)
	{
		for(int i=0;i<htab.nrElemente;i++)
		{
			Produs* tmp=htab.vector[i];
			if(tmp!=NULL)
			{
				printf("Lista nr. %d:\n",i); 
				printf(" %d %s %f\n",tmp->id,tmp->denumire,tmp->pret);
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
			Produs* info=creareInfoUtil(id, denumire, pret);
			inserareHashTable(htab, info);
				
			fscanf(pfile,"%d",&id);
		}
		fclose(pfile);
		parcurgereHashTable(htab);
	}
}
