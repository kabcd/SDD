#include<iostream>
using namespace std;
struct Produs{
	int id;
	float pret;
	char* denumire;
};
//stiva - implementata ca lista simplu inlantuita circulara
//LIFO
//adaugarea unui element la inceputul cozii(push)
//extragerea unui element de la inceputul cozii(pop)
struct NodStiva{
	Produs* infoUtil;
	NodStiva* next;
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
NodStiva* creareNod(Produs* infoUtil)
{
	NodStiva* tmp=NULL;
	tmp=(NodStiva*)malloc(sizeof(NodStiva));
	tmp->infoUtil=infoUtil;
	tmp->next=NULL;
	return tmp;
}
void pushElementStiva(NodStiva* &head, NodStiva* nod)
{
	if(head==NULL)
	{
		head=nod;
		head->next=head;
	}
	else
	{
		NodStiva* tmp=head;
		while(tmp->next!=head)
			tmp=tmp->next;
		tmp->next=nod;
		nod->next=head;
		head=nod;
	}
}
NodStiva* popElementStiva(NodStiva *&head)
{
	NodStiva* element=head;
	if(head==head->next)
		head=NULL;
	else
	{
		NodStiva* tmp=head;
		while(tmp->next!=head)
			tmp=tmp->next;
		tmp->next=head->next;
		head=head->next;
	}
	return element;
}
void main()
{
	FILE *pfile=fopen("produse.txt","r");
	NodStiva* head=NULL;
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
			NodStiva* nod=creareNod(infoUtil);
			pushElementStiva(head, nod);
				
			fscanf(pfile,"%d",&id);
		}
		fclose(pfile);
	}
	while(head!=NULL)
	{
		NodStiva* tmp=popElementStiva(head);
		printf(" %d %s %f\n",tmp->infoUtil->id, tmp->infoUtil->denumire, tmp->infoUtil->pret);
	}

}
