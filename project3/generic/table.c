//Lab 3 Coen12 4/3/2017 Joseph Sindelar
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "set.h"
//Inclusions

#define MAX_WORD_LENGTH [30]
#define EMPTY 0
#define FILLED 1
#define DELETED 2
#define SET struct set //Makes a data type
struct set
{
	int count;
	int length;
	void **data;
	char *flags;
	int (*compare)();
	unsigned (*hash)(); //Replacement functions for generic
};

static int search(SET *sp, void *elt, bool *found); //For debugging

SET *createSet(int maxElts, int (*compare)(), unsigned (*hash)()) //Creates a set O(n)
{
	SET *sp;
	sp=malloc(sizeof(SET));
	assert(sp!=NULL);
	sp->count=0;
	sp->length= maxElts;
	sp->data=malloc(sizeof(void*)*maxElts);
	sp->flags=malloc(sizeof(void)*maxElts);
	assert(sp->data!=NULL);
	int i;
	for(i=0;i<maxElts;i++)
		sp->flags[i]=EMPTY;
	sp->compare=compare;
	sp->hash=hash;
	return sp;
}

void destroySet(SET *sp) //Destroys a node O(1)
{
	free (sp->data);
	free (sp->flags);
	free (sp);
}

int numElements (SET *sp) //provides the number of elements O(1)
{
	assert(sp!=NULL);
	return (sp->count);
}

void addElement(SET *sp, void *elt) //Adds an element into a set O(n)
{
	assert(sp!=NULL);
	int i;
	bool found;
	i = search(sp, elt, &found);
	if(sp==NULL || elt==NULL)
			return;
	if (found==false)
	{
		sp->data[i]=elt;
		assert(sp->data[i]!=NULL);
		sp->count++;
		sp->flags[i]=FILLED;
	}	
	return;
}

void removeElement(SET *sp, void *elt) //Removes an element from a set O(n)
{
	int locn;
	bool found;
	assert (sp!=NULL && elt!=NULL);
	locn=search(sp, elt, &found);
	if (found==true)
	{
		sp->flags[locn]=DELETED;
		sp->count--;
	}
	return;
}

void  *findElement (SET *sp, void *elt) //Searches for an elememnt in a set O(n)
{
	int locn;
	bool found;
	assert(sp!=NULL);
	locn=search(sp, elt, &found);
	if (found==true)
		return sp->data[locn];
	return NULL;
}

static int search (SET *sp, void *elt, bool *found) //Searches for where the element should be put in or if there is a match O(n)
{
	int locn, diff, i, j, first;
	assert(sp!=NULL);
	assert(elt!=NULL);
	first=0;
	locn= (sp->hash(elt)%sp->length);
	for(i=0;i<sp->length;i++)
	{
		j=(locn+i)%sp->length;
		if (sp->flags[j]==EMPTY)
		{
			*found = false;
			if (first!=0)
				return first;
			else
				return j;
		}
		if (sp->flags[j]==DELETED && first==0)
			first=j;
		if (sp->flags[j]==FILLED)
		{
			diff=(*sp->compare)(elt, sp->data[j]);
			if (diff==0)
			{
				*found = true;
				return j;
			}
		}
	}
	*found = false;
	return j;
}

void *getElements(SET *sp) //Returns the data O(n)
{
	int counter=0;
	assert(sp!=NULL);
	void **a;
	a=malloc(sizeof(void*)*sp->count);
	int i=0;
	for (i=0;i<sp->length;i++)
	{
		if (sp->flags[i]==FILLED)
		{
			a[counter]=sp->data[i];
			counter++;
		}
	}
	return a;
}


