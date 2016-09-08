#include<iostream>
using namespace std;
struct Produs{
	int id;
	float pret;
	char* denumire;
};
//coada - implementata ca lista dublu inlantuita circulara
//FIFO
//adaugarea unui element la sfarsitul cozii(put)
//extragerea unui element de la inceputul cozii(get)
struct NodCoada{
	Produs* infoUtil;
	NodCoada* next;
	NodCoada* prev;
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
NodCoada* creareNod(Produs* infoUtil)
{
	NodCoada* tmp=NULL;
	tmp=(NodCoada*)malloc(sizeof(NodCoada));
	tmp->infoUtil=infoUtil;
	tmp->next=NULL;
	tmp->prev=NULL;
	return tmp;
}
void putElementCoada(NodCoada* &head, NodCoada* nod)
{
	if(head==NULL)
	{
		head=nod;
		head->next=head;
		head->prev=head;
	}
	else
	{
		nod->next=head;
		nod->prev=head->prev;
		head->prev=nod;
		nod->prev->next=nod;
	}
}
bool emptyCoada(NodCoada* head)
{ 
	if(head==NULL)
		return false;
	else
		return true;
}
NodCoada* getElementCoada(NodCoada *&head)
{
	NodCoada* tmp=head;
	if(head==head->next && head==head->prev)
		head=NULL;
	else
	{
		head=tmp->next;
		head->prev=tmp->prev;
		head->prev->next=head;
	}
	return tmp;
}
void main()
{
	FILE *pfile=fopen("produse.txt","r");
	NodCoada* head=NULL;
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
			NodCoada* nod=creareNod(infoUtil);
			putElementCoada(head, nod);
			fscanf(pfile,"%d",&id);
		}
		fclose(pfile);
	}
	while(emptyCoada(head))
	{
		NodCoada* tmp=getElementCoada(head);
		printf(" Produs: %d %s %f\n",tmp->infoUtil->id, tmp->infoUtil->denumire, tmp->infoUtil->pret);
	}
}
