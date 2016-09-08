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
//inserare la sfarsit
void inserareSfarsit(Nod* &head, Nod* nod)
{
	if(head==NULL)
	{
		head=nod;
		nod->next=head;
	}
	else
	{
		Nod* tmp=head;
		while(tmp->next!=head)
			tmp=tmp->next;
		tmp->next=nod;
		nod->next=head;
	}
}
void parcurgereLista(Nod* head)
{
	Nod* tmp=head;
	while(tmp->next!=head)
	{
		printf(" %d %s %f\n",tmp->infoUtil->id, tmp->infoUtil->denumire, tmp->infoUtil->pret);
		tmp=tmp->next;
	}
	printf(" %d %s %f\n",tmp->infoUtil->id, tmp->infoUtil->denumire, tmp->infoUtil->pret);
}
void main()
{
	FILE *pfile=fopen("produse.txt","r");
	Nod* head=NULL;
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
			inserareSfarsit(head, nod);
				
			fscanf(pfile,"%d",&id);
		}
		fclose(pfile);
		parcurgereLista(head);
	}
}