#include<iostream>
using namespace std;
struct Produs{
	int id;
	float pret;
	char* denumire;
};
struct HeapItem
{
	Produs cheie;
	int data;
};
struct Heap{
	HeapItem* *elemente;
	int nrElemente;
	int dimensiune;
};
Produs creareInfo(int id, char* denumire, float pret)
{
	Produs tmp;
	tmp.id=id;
	tmp.denumire=(char*)malloc(strlen(denumire)+1);
	strcpy(tmp.denumire, denumire);
	tmp.pret=pret;
	return tmp;
}
HeapItem* creareHeapItem(Produs info, int data)
{
	HeapItem* tmp=NULL;
	tmp=(HeapItem*)malloc(sizeof(HeapItem));
	tmp->cheie=info;
	tmp->data=data;
	return tmp;
}
void initHeap(Heap &heap, int dim)
{
	heap.elemente=(HeapItem* *)malloc(sizeof(HeapItem*)*dim);
	heap.nrElemente=0;
	heap.dimensiune=dim;
	memset(heap.elemente, 0, sizeof(HeapItem*)*dim);
}
void ReHeapUp(Heap &heap, int first, int last)
{
	int parinte=0;
	if(last>first)
		parinte=(last-1)/2;
	if(heap.elemente[last]->cheie.id>heap.elemente[parinte]->cheie.id)
	{
		HeapItem* aux=heap.elemente[last];
		heap.elemente[last]=heap.elemente[parinte];
		heap.elemente[parinte]=aux;
		ReHeapUp(heap, first, parinte);
	}
}
void Enqueue(Heap &heap, HeapItem* item)
{
	if(heap.nrElemente<heap.dimensiune)
	{
		heap.elemente[heap.nrElemente]=item;
		ReHeapUp(heap, 0, heap.nrElemente);
		heap.nrElemente++;
	}
}
void printHeap(Heap heap)
{
	for(int i=0;i<heap.nrElemente;i++)
		printf("%d->%d %s %f\n", heap.elemente[i]->data, heap.elemente[i]->cheie.id, heap.elemente[i]->cheie.denumire, heap.elemente[i]->cheie.pret);
}
void ReHeapDown(Heap &heap, int first, int last)
{
	int leftChild=2*first+1;
	int rightChild=2*first+2;
	int maxChild=0;
	if(leftChild<=last)
	{
		if(leftChild==last)
			maxChild=leftChild;
		else
		{
			if(heap.elemente[leftChild]->cheie.id>heap.elemente[rightChild]->cheie.id)
				maxChild=leftChild;
			else
				maxChild=rightChild;
		}
		if(heap.elemente[maxChild]->cheie.id<heap.elemente[first]->cheie.id)
		{
			HeapItem* aux=heap.elemente[first];
			heap.elemente[first]=heap.elemente[maxChild];
			heap.elemente[maxChild]=aux;
			ReHeapDown(heap, maxChild, last);
		}
	}
}
HeapItem *Dequeue(Heap &heap)
{
	if(heap.nrElemente>0)
	{
		HeapItem* element=heap.elemente[0];
		heap.elemente[0]=heap.elemente[heap.nrElemente-1];
		heap.nrElemente--;
		ReHeapDown(heap, 0, heap.nrElemente-1);
		return element;
	}
	return NULL;
}
void main()
{
	FILE *pfile=fopen("produse.txt","r");
	Heap heap;
	initHeap(heap, 10);
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
			Produs info=creareInfo(id, denumire, pret);
			HeapItem* item=creareHeapItem(info, heap.nrElemente);
			Enqueue(heap, item);

			fscanf(pfile,"%d",&id);
		}
		fclose(pfile);
	}
	printHeap(heap);

	HeapItem* item=NULL;
	while((item=Dequeue(heap))!=NULL)
	{
		printf("-----------------\n");
		printf("%d->%d %s %f\n", item->data, item->cheie.id, item->cheie.denumire, item->cheie.pret);
	}
}