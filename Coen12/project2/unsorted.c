//Lab 2 Coen12
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "set.h"
//Inclusions

#define MAX_WORD_LENGTH [30]

#define SET struct set //Data type
struct set
{
	int count;
	int length;
	char **data;
};

static int search(SET *sp, char *elt); //Debugging

SET *createSet(int maxElts) //Creates nodes O(1)
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

void destroySet(SET *sp) //Destroys Node O(n)
{
	int i;
	for (i=0;i<sp->count;i++)
		free (sp->data[i]);
	free (sp->data);
	free (sp);
}

int numElements (SET *sp) //O (1)
{
	assert(sp!=NULL);
	return (sp->count);
}

void addElement(SET *sp, char *elt) //O(1) //Adds element inside the data in the node
{
	assert(sp!=NULL);
	int diff;
	diff = search(sp, elt);
	if (diff==-1)
	{
		sp->data[sp->count]=strdup(elt);
		assert(sp->data[sp->count]!=NULL);
		sp->count++;
	}	
	return;
}

void removeElement(SET *sp, char *elt) // O(1) //Removes an element
{
	int locn;
	assert (sp!=NULL && elt!=NULL);
	locn=search(sp, elt);
	if (locn!=-1)
	{
		free (sp->data[locn]);
		sp->data[locn]=sp->data[--sp->count];
	}
	return;
}

char *findElement (SET *sp, char *elt) //Returns an element that was searched for O(n)
{
	int locn;
	assert(sp!=NULL);
	locn=search(sp, elt);
	if (locn!=-1)
		return sp->data[locn];
	return NULL;
}

static int search (SET *sp, char *elt) //O(n) Searches for an element
{
	int i=0;
	assert(sp!=NULL);
	assert(elt!=NULL);
	int diff;
	while (i<sp->count)
	{	
		diff=strcmp(elt, sp->data[i]);
		if (diff==0)
			return i;
		i++;
	}
	return -1;
}

char **getElements(SET *sp) //Returns a copy of the DATA so it does not get changed O(n)
{
	assert(sp!=NULL);
	char **a;
	a=malloc(sizeof(char*)*sp->count);
	int i=0;
	for (i=0;i<sp->count;i++)
		a[i]=sp->data[i];
	return a;
}


