//Lab 2 Coen12
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "set.h"
//Inclusions

#define MAX_WORD_LENGTH [30]

#define SET struct set //Makes a data type
struct set
{
	int count;
	int length;
	char **data;
};

static int search(SET *sp, char *elt, bool *found); //For debugging

SET *createSet(int maxElts) //Creates a set O(1)
{
	SET *sp;
	sp=malloc(sizeof(SET));
	assert(sp!=NULL);
	sp->count=0;
	sp->length= maxElts;
	sp->data=malloc(sizeof(char*)*maxElts);
	assert(sp->data!=NULL);
	return sp;
}

void destroySet(SET *sp) //Destroys a node O(n)
{
	int i;
	for (i=0;i<sp->count;i++)
		free (sp->data[i]);
	free (sp->data);
	free (sp);
}

int numElements (SET *sp) //provides the number of elements O(1)
{
	assert(sp!=NULL);
	return (sp->count);
}

void addElement(SET *sp, char *elt) //Adds an element into a set O(n)
{
	assert(sp!=NULL);
	int i, j;
	bool found;
	i = search(sp, elt, &found);
	if(sp==NULL || elt==NULL)
			return;
	if (found==false)
	{
		for(j=sp->count;j>i;j--)
			sp->data[j]=sp->data[j-1];
		sp->data[i]=strdup(elt);
		assert(sp->data[i]!=NULL);
		sp->count++;
	}	
	return;
}

void removeElement(SET *sp, char *elt) //Removes an element from a set O(n)
{
	int locn;
	int j;
	bool found;
	assert (sp!=NULL && elt!=NULL);
	locn=search(sp, elt, &found);
	if (found==true)
	{
		free(sp->data[locn]);
		for (j=locn+1;j<sp->count;j++)
			sp->data[j-1]=sp->data[j];
		sp->count--;
	}
	return;
}

char *findElement (SET *sp, char *elt) //Searches for an elememnt in a set O(n)
{
	int locn;
	bool found;
	assert(sp!=NULL);
	locn=search(sp, elt, &found);
	if (found==true)
		return sp->data[locn];
	return NULL;
}

static int search (SET *sp, char *elt, bool *found) //Searches for where the element should be put in or if there is a match O(log n)
{
	int lo, hi, mid, diff;
	assert(sp!=NULL);
	assert(elt!=NULL);
	lo = 0;
	hi = sp->count-1;
	while (lo<=hi)
	{	
		mid=(lo+hi)/2;
		diff=strcmp(elt,sp->data[mid]);
		if (diff<0)
			hi=mid-1;
		else if (diff>0)
			lo=mid+1;
		else
		{
			*found = true;
			return mid;
		}
	}
	*found = false;
	return lo;
}

char **getElements(SET *sp) //Returns the data O(n)
{
	assert(sp!=NULL);
	char **a;
	a=malloc(sizeof(char*)*sp->count);
	int i=0;
	for (i=0;i<sp->count;i++)
		a[i]=sp->data[i];
	return a;
}


