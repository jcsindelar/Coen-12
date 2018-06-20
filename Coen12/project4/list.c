//Lab 4 Coen12 Joseph Sindelar 
// May 9th, 2017

#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "list.h"
// Inclusions and Headers

//Need two structs

#define LIST struct list //Makes a data type
struct list
{
	//head count and compare
	struct node *head;
	int count;
	int (*compare)();
};

#define NODE struct node //Makes a node data type
struct node
{
	void *data;
	struct node *next, *prev;
};

LIST *createList(int (compare)()) //Creates a list O(1)
{
	LIST *lp;
	lp=malloc(sizeof(LIST));
	NODE *dummyNode = malloc(sizeof(NODE));
	assert(lp!=NULL);
	lp->head = dummyNode;
	lp->count=0;
	lp->compare=compare;
	dummyNode->next=dummyNode;
	dummyNode->prev=dummyNode;
	return lp;
}
void destroyList (LIST *lp) //Destroys the list O(n)
{
	assert (lp != NULL);
	NODE *np;
	NODE *dp;
	dp=lp->head;
	np=dp->next;
	while (np != lp->head)
	{
		free (dp);
		dp=np;
		np=np->next;
	}
}

int numItems (LIST *lp) //Returns count O(1)
{
	assert(lp!=NULL);
	return (lp->count);
}

void addFirst (LIST *lp, void *item) //Adds into the front O(1)
{
	assert(lp!=NULL);
	NODE *newNode = malloc(sizeof(NODE));
	newNode->next = lp->head->next;
	newNode->prev = lp->head;
	newNode->next->prev=newNode;
	lp->head->next = newNode;
	newNode->data = item;
	lp->count++;
}

void addLast (LIST *lp, void *item) //Adds into the back O(1)
{
	assert(lp!=NULL);
	NODE *newNode = malloc(sizeof(NODE));
	NODE *np;
	np=lp->head->prev;
	newNode->next=lp->head;
	newNode->prev=np;
	np->next=newNode;
	lp->head->prev=newNode;
	newNode->data = item;
	lp->count++;
}

void *removeFirst (LIST *lp) //Removes the first item in O(1)
{
	assert(lp!=NULL);
	NODE *np;
	np=lp->head->next;
	if (np==lp->head)
		return NULL;
	lp->head->next=np->next;
	np->next->prev=np->prev;
	void *temp;
	temp = np->data;
	free(np);
	lp->count--;
	return temp;
}

void *removeLast (LIST *lp) //Removes the last item O(1)
{
	assert(lp!=NULL);
	NODE *np;
	np=lp->head->prev;
	np->prev->next=lp->head;
	lp->head->prev=np->prev;
	void *temp;
	temp = np->data;
	free(np);
	lp->count--;
	return temp;
}

void *getFirst (LIST *lp) //Returns the first item data O(1)
{
	assert(lp!=NULL);
	NODE *np;
	np=lp->head->next;
	if (np==lp->head)
		return NULL;
	return np->data;
}

void *getLast (LIST *lp) //Returns the last item in the list O(1)
{
	assert(lp!=NULL);
	if (lp->head->next == lp->head)
		return NULL;
	NODE *np;
	np=lp->head->prev;
	return np->data;
}

void removeItem (LIST *lp, void *item) //Removes an item from the list O(n)
{
	assert(lp!=NULL);
	assert(lp->compare != NULL);
	NODE *np;
	int diff;
	np=lp->head;
	while (np->next != lp->head)
	{
		np=np->next;
		diff=(*lp->compare)(item, np->data);
		if (diff==0)
		{
			np->next->prev=np->prev;
			np->prev->next=np->next;
			lp->count--;
			free (np);
			return;
		}
	}
	return;
}

void *findItem (LIST *lp, void *item) //Searches for an item O(n)
{
	assert(lp!=NULL);
	assert(lp->compare != NULL);
	NODE *np;
	int diff;
	np=lp->head;
	while (np->next != lp->head)
	{
		np=np->next;
		diff=(*lp->compare)(item, np->data);
		if (diff==0)
			return np->data;
	}
	return NULL;
}

void *getItems (LIST *lp) //Adds items into an array O(n)
{
	assert(lp!=NULL);
	NODE *np;
	np=lp->head->next;
	void **a;
	a=malloc(sizeof(void*)*lp->count);
	int i=0;
	for(i=0;i<lp->count;i++)
	{
		a[i]=np->data;
		np=np->next;
	}
	return a;
}
