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
	int gradEchilibru;
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
	tmp->gradEchilibru=0;
	return tmp;
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
int getGE(NodArbore* radacina)
{
	return getInaltime(radacina->drept)-getInaltime(radacina->stang);
}
NodArbore* rotireRSD(NodArbore* pivot)
{
	NodArbore* copil=pivot->stang;
	pivot->stang=copil->drept;
	copil->drept=pivot;
	copil->gradEchilibru=getGE(copil);
	pivot->gradEchilibru=getGE(pivot);
	return copil;
}
NodArbore* rotireRSS(NodArbore* pivot)
{
	NodArbore* copil=pivot->drept;
	pivot->drept=copil->stang;
	copil->stang=pivot;
	copil->gradEchilibru=getGE(copil);
	pivot->gradEchilibru=getGE(pivot);
	return copil;
}
NodArbore* rotireRSDRSS(NodArbore* pivot)
{
	pivot->stang=rotireRSS(pivot->stang);
	pivot=rotireRSD(pivot);
	return pivot;
}
NodArbore* rotireRSSRSD(NodArbore* pivot)
{
	pivot->drept=rotireRSD(pivot->drept);
	pivot=rotireRSS(pivot);
	return pivot;
}
NodArbore* rebalansare(NodArbore* radacina)
{
	radacina->gradEchilibru=getGE(radacina);
	if(radacina->gradEchilibru==2)
	{
		NodArbore* copil=radacina->drept;
		if(copil->gradEchilibru==1)
			radacina=rotireRSS(radacina);
		else
			radacina=rotireRSSRSD(radacina);
	}
	else if(radacina->gradEchilibru==-2)
	{
		NodArbore* copil=radacina->stang;
		if(copil->gradEchilibru==-1)
			radacina=rotireRSD(radacina);
		else
			radacina=rotireRSDRSS(radacina);
	}
	return radacina;
}
void inserareNodArbore(NodArbore* &radacina, NodArbore* nod)
{
	if(radacina==NULL)
		radacina=nod;
	else if(nod->infoUtil->id < radacina->infoUtil->id)
		inserareNodArbore(radacina->stang,nod);
	else if(nod->infoUtil->id > radacina->infoUtil->id)
		inserareNodArbore(radacina->drept,nod);
	radacina=rebalansare(radacina);
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

	printf("Inaltime arbore: %d \n",getInaltime(radacina));

	inserareNodArbore(radacina, creareNodArbore(creareInfoUtil(26, "ProdusNou", 8.5)));
	printf("-----Rebalansare arbore-------\n");
	parcurgereRSD(radacina);
}
