//Joseph Sindelar Lab 5
#include "pqueue.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
//Inclusions

//Definitions
#define START_LENGTH 10
#define p(x) (((x)-1)/2)
#define l(x) (((x)*2)+1)
#define r(x) (((x)*2)+2)

//Struct for queue
struct pqueue
{
	int count;
	int length;
	void **data;
	int (*compare)();
};

//Creates a queue O(1)
PQ *createQueue(int (*compare)())
{
	PQ *pq;
	pq=malloc(sizeof(PQ));
	pq->compare=compare;
	pq->count=0;
	pq->length=START_LENGTH;
	pq->data=malloc(sizeof(void *)*pq->length);
	return pq;
}

//Destroys the queue O(1)
void destroyQueue(PQ *pq)
{
	assert(pq!=NULL);
	free (pq->data);
	free(pq);
}

//Returns number of entries O(1)
int numEntries(PQ *pq)
{
	assert(pq!=NULL);
	return(pq->count);
}

//Adds an entry into the queue O(n)
void addEntry(PQ *pq, void *entry)
{
	assert(pq!=NULL);
	if(pq->count + 1>pq->length)
	{
		pq->data=realloc(pq->data, sizeof(void*) * pq->length *2);
		pq->length=pq->length *2;
	}
	int i;
	i=pq->count;
	pq->data[i]=entry;
	int parent =p(i);

	while(parent>=0)
	{
		//printf("before if\n");
		if((*pq->compare)(pq->data[parent], pq->data[i]) > 0)
		{
			void *temp = pq->data[i];
			pq->data[i]=pq->data[parent];
			pq->data[parent]=temp;
		}
		else
			break;
		i=parent;
		parent=p(parent);
	}
	pq->count++;
}

//Removes an entry from the queue O(n)
void *removeEntry (PQ *pq)
{
	assert(pq!=NULL);
	int cp1;
	int i=0;
	void *child;
	void *x;
	int min=0;
	child=pq->data[i];
	pq->data[i]=pq->data[pq->count-1];
	pq->count--;
	while(l(i)<pq->count)
	{
		if (r(i)<pq->count)
		{	
			cp1=(*pq->compare)(pq->data[l(i)], pq->data[r(i)]);
			if(cp1<0)
				min=l(i);
			else
				min=r(i);
		}
		else
			min=l(i);

		if (((*pq->compare)(pq->data[i], pq->data[min]))>0)
		{
			x=pq->data[i];
			pq->data[i]=pq->data[min];
			pq->data[min]=x;
		}
		else
			break;
		i=min;
	}
	return child;
}
