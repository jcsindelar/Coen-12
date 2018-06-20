//Joseph Sindelar Lab 4

#include "set.h"
#include "list.h"
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
//Inclusions

int average=20; //Average inputted from the user

struct list //To define the opaque data types
{
	struct node *head;
	int count;
	int (*compare)();
};

struct node //" "
{ 
	void *data;
	struct node *next, *prev;
};

struct set //" "
{
	LIST **lists;
	int count;
	int length;
	int (*compare)();
	unsigned (*hash)();
};

SET *createSet(int maxElts, int (*compare)(), unsigned (*hash)()) //Creates a set O(n)
{
	SET *sp;
	sp=malloc(sizeof(SET));
	sp->count=0;
	sp->length=maxElts/average;
	sp->compare=compare;
	sp->hash=hash;
	int i;
	sp->lists=malloc(sizeof(LIST*)*sp->length);
	for (i=0;i<sp->length;i++)
		sp->lists[i]=createList(compare);
	return sp;
}

void destroySet(SET *sp)// Destroys sets O(n)
{
	int i;
	for (i=0;i<sp->length;i++)
		free(sp->lists[i]);
	free(sp->lists);
	free(sp);
}

int numElements(SET *sp)//Returns count O(1)
{
	assert(sp!=NULL);
	return sp->count;
}

void addElement(SET *sp, void *elt) //Adds an element O(n)
{
	assert(sp!=NULL && elt !=NULL);
	int index = (*sp->hash)(elt) % sp->length;
	if (findItem(sp->lists[index], elt)==NULL)
	{
		addFirst(sp->lists[index], elt);
		sp->count++;
	}
}

void removeElement(SET *sp, void *elt) //Removes an element O(n^2)
{
	assert(sp!=NULL);
	int index = (*sp->hash)(elt) % sp->length;
	if (findItem(sp->lists[index], elt)!=NULL)
	{
		removeItem(sp->lists[index], elt);
		sp->count--;
	}
}

void *findElement(SET *sp, void *elt) //Find elements O(n)
{
	assert(sp!=NULL);
	int index = (*sp->hash)(elt) % sp->length;
	return findItem(sp->lists[index], elt);
}

void *getElements(SET *sp) //Puts all elements into an array O(n^2)
{
	assert(sp!=NULL);
	int counter=0;
	void **a;
	a=malloc(sizeof(void*)*sp->count);
	int i, j;
	j=0;
	struct node *np;
	for (i=0;i<sp->length;i++)
	{
		int count=numItems(sp->lists[i]);
		if(count != 0)
		{
			np=sp->lists[i]->head->next;
			while (np != sp->lists[i]->head)
			{
				a[j]=np->data;
				j++;
				counter++;
				np= np->next;
			}
		}
	}
	return a;
}
