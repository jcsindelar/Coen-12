#include <stdio.h>
#include <stdlib.h>
//Joseph Sindelar
int count=0;
void createDataSet();
int destroyDataSet();
int delete();
int searchid();
int main();
int students;
int idtrack=0;//Global variables used to keep a count, although I am not sure if this was necessary

typedef struct dubs{//Makes the UI insert function nicer
	int cnt;
	int idnum;
}dubs;

dubs insert();

typedef struct Data{//Chose this as it allows a single array with two values per slot.
	int ID;
	int AGE;
}Data;
Data array[3000];//Again the assignment said I may assume the max size is 3000. 

/*
Fills my array with 1000 students
Runtime O(n)
Void function
*/

void createDataSet(int students){//Populates my array with 1000 students, O(n)
	srand(0);
	int i;
	int agetemp;
	for(i=0;i<students;i++)
		array[i].ID=-1;
	for (i=0;i<1000;i++){
		agetemp=rand() % (30+1-18)+18;
		insert(agetemp);
	}
	printf("Random set of %d generated\n",count);//Verifys the success
}

/*
Turns all values to -1
Runtime is O(n) 
Returns count to verify that all values were successfully removed indiviually.
  */

int destroyDataSet(){//Turns all values to -1. Could be modified if each value did not have to be removed individually. O(n)
	int i;
	int top=count;
	for (i=0;i<idtrack+2;i++)
	{
		if(array[i].ID!=-1){
			array[i].ID=-1;
			array[i].AGE=-1;
			count--;
		}
	}
	return count;//Verify success for all entries
}
/*
   Deletes an individual entry passed to it from main
   Uses the hash function to find it
   Runtime O(1)
   Returns an integer to main to make the UI nicer
*/
int delete(int id){//Deletes an individual entry O(1)
	int h;
	h=(id%2003);
	if (array[h].ID==id){
		if (h==idtrack%2003){
			h--;
			while (array[h].ID==-1)
				h--;
			idtrack=array[h].ID;
			count--;
		}
		array[h]=array[idtrack%2003];
		count--;
		return count;
	}
return 0;
}
/*
Inserts an age and assigns that age a unique ID
Runtime: 0(1)
Returns a datatype to the main function to make the UI nicer
   */
dubs insert(int age){//Inserts a single entry O(1)
	dubs r;
	if (count==1001){
			r.cnt=0;
			r.idnum=0;
			return r;
	}
	int h;
	idtrack=(idtrack+rand()%(2+1-1)+1);
	h=(idtrack%2003);
	array[h].AGE=age;
	array[h].ID=h;
	count++;
	r.idnum=array[h].ID;
	r.cnt=count;
	return r;
}

/*
Searches for an ID using the hash
Runtime of O(1)
Returns an integer for the benefit of the UI
*/

int searchid(int id){//Searches for a single ID O(1)
	int h;
	h=(id%2003);
	printf("%d\n",h);
	printf("%d\n",id);
	if (array[h].ID==id)
		return h;
	return 0;
}
