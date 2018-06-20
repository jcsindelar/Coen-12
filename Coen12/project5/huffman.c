//Joseph Sindelar
#include "pack.h"
#include "pqueue.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>
//Inclusions

#define NODE struct node

//New compare function
int Newcompare(int x, int y)
{
	if (x>y)
		return x;
	else
		return y;
}

//Main function O(n)
int main (int argc, char *argv[])
{
	printf("start\n");
	int i;
	char temp;
	int counts[257];
	NODE *anode[257];
	FILE *fp;
	fp=fopen(argv[1], "r");
	
	//Does step 1 counting
	for (i=0;i<257;i++)
	{
		fscanf(fp,"%c", &temp);
		counts[(int)temp]++;
	}
	fclose(fp);

	printf("counts\n");

	PQ *pq=createQueue(Newcompare);
	
	//Step 2
	int j;
	for (j=0;j<257;j++)
	{
		anode[j]=malloc(sizeof(NODE));
		anode[j]->parent=NULL;
		anode[j]->count=counts[j];
		addEntry(pq, anode[j]);
	}	
	printf("while\n");
	
	//Step 3
	while(numEntries(pq)>1)
	{
		NODE *child1;
		NODE *child2;
		child1=removeEntry(pq);
		child2=removeEntry(pq);
		NODE *top;
		top=malloc(sizeof(NODE));
		top->parent=NULL;
		child1->parent=top;
		child2->parent=top;
		addEntry(pq, top);
	}
	//Step 4
	printf("after while\n");
	int f;
	int printing[257];
	for(f=0;f<257;f++)
	{
		printing[f]=0;
	}
	printf("here\n");
	
	//Step 5
	NODE *temps;
	for(i=0;i<257;i++)
	{
		int count=0;
		if (anode[i]!=NULL)
		{
			temps=anode[i];
			while(temps->parent!=NULL)
			{
				count++;
				temps=temps->parent;
			}
			int total=count*counts[i];
			if(isprint(i)==0)
				printf("'%03o': %d x %d bits = %d bits\n",i,counts[i],count,total);
			else
				printf("'%c': %d x %d bits = %d bits\n",i,counts[i],count,total);
		}
	}
	pack(argv[1],argv[2],anode);
	printf("end\n");
	return 0;
}
