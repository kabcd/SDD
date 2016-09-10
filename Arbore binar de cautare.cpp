#include<iostream>
using namespace std;
struct Produs{
	int id;
	float pret;
	char* denumire;
};
struct NodArbore{
	Produs* infoUtil;
	NodArbore* stang;
	NodArbore* drept;
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
NodArbore* creareNodArbore(Produs* infoUtil)
{
	NodArbore* tmp=NULL;
	tmp=(NodArbore*)malloc(sizeof(NodArbore));
	tmp->infoUtil=infoUtil;
	tmp->stang=tmp->drept=NULL;
	return tmp;
}
void inserareNodArbore(NodArbore* &radacina, NodArbore* nod)
{
	if(radacina==NULL)
		radacina=nod;
	else
		if(nod->infoUtil->id < radacina->infoUtil->id)
			inserareNodArbore(radacina->stang,nod);
		else
			if(nod->infoUtil->id > radacina->infoUtil->id)
				inserareNodArbore(radacina->drept,nod);
}
int max(int a, int b)
{
	return (a>b)? a:b;
}
int getInaltime(NodArbore* radacina)
{
	if(radacina!=NULL)
		return 1+max(getInaltime(radacina->drept), getInaltime(radacina->stang));
	else
		return 0;
}
void parcurgereRSD(NodArbore* radacina)
{
	if(radacina!=NULL)
	{
		printf("%d \n",radacina->infoUtil->id);
		parcurgereRSD(radacina->stang);
		parcurgereRSD(radacina->drept);
	}
}
void parcurgereSRD(NodArbore* radacina)
{
	if(radacina!=NULL)
	{
		parcurgereSRD(radacina->stang);
		printf("%d \n",radacina->infoUtil->id);
		parcurgereSRD(radacina->drept);
	}
}
void parcurgereSDR(NodArbore* radacina)
{
	if(radacina!=NULL)
	{
		parcurgereSDR(radacina->stang);
		parcurgereSDR(radacina->drept);
		printf("%d \n",radacina->infoUtil->id);
	}
}
void main()
{
	FILE *pfile=fopen("produse.txt","r");
	NodArbore* radacina=NULL;
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
			NodArbore* nod=creareNodArbore(infoUtil);
			inserareNodArbore(radacina, nod);

			fscanf(pfile,"%d",&id);
		}
		fclose(pfile);
	}
	printf("------Parcurgere PreOrdine-----------\n");
	parcurgereRSD(radacina);

	printf("------Parcurgere InOrdine-----------\n");
	parcurgereSRD(radacina);

	printf("------Parcurgere PostOrdine-----------\n");
	parcurgereSDR(radacina);

	printf("Inaltime arbore: %d ",getInaltime(radacina));
}


