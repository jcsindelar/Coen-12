#include <stdio.h>
#include <stdlib.h>
//Joseph Sindelar
int count=0;
int maxAge=0;
int minAge=0;
int flag=0;
int idtrack=0;
void createDataSet();
int destroyDataSet();
int delete();
int students;
int maxage();
int main();//Declared these globals becuase I did not know I could just have a header file.

typedef struct dubs{//Just used for a return function. Not necessary, but makes things easier to understand in the UI
	int cnt;
	int idnum;
}dubs;

dubs insert();

int array[32][3000];//Assignment says assume max number is 3000, so I assume I can write this.
//Assignment also has age parameters. Therefore I capped the maximum age and minimum age. Can be modified easily if need be.

/*
   Populates my 2D array with value that are sorted by age.
   Calls the insert function
   Also fills slots that do not get an ID with -1
   O(n)
   Void function
 */

void createDataSet(int students){//Generates a 2D int array capable of sorting IDs based on age. Calls insert function. O(n).
	srand(0);
	int i=0;
	int j;
	int k;
	int agetemp;
	for (j=18;j<31;j++){//Age parameters here could be changed for different values
		array[j][0]=j;
		for(k=1;k<students;k++)
			array[j][k]=-1;
	}
	for (i=0;i<1000;i++){
		agetemp=rand() % (30+1-18)+18;
		if (i==0){
			maxAge=agetemp;
			minAge=agetemp;
		}
		insert(agetemp);
	}
	printf("Random set of %d generated\n",count);
}

/*
Clears the values in the array to -1
No need to free as the array is static
O(n)
Returns the count to verify items have been removed successfully.
Could be done differently if we do not need to remove each item individually.
Returns count to verify success.
 */

int destroyDataSet(){//Clears the array back to -1. No need to free as the data is static. O(n)
	int i;
	int j;
	for (i=18;i<31;i++)
	{
		j=1;
		while(array[i][j]!=-1){
			array[i][j]=-1;
			j++;
			count--;
		}
	}
	return count;
}
/*
Deletes an entire age group for an age value passed to it from main.
Also updates the maxage values if need be.
Bounded by the age parameters from the assignment.
O(n)
Could be changed to O(1) if we did not need to keep track of the count.
Returns newcount to verify that a change was made or not.
 */

int delete(int age){//Because of the age parameters this function is relatively simple. O(n) or O(1) depending on how many students are being removed. 
	if (age>30)
		return count;//While the assignment does not explicitly ask for count, I inlcude it for the benefit of the UI
	if (age<18)
		return count;//If I did not need to include the count, I could just make the first value in the row -1, and modify my insert function a bit to overwrite deleted values. 
	int i=1;//If I did this my new big O would be O(1), but I assume a count is a valuable inclusion.
	int newcount;
	if (age==maxAge)
		maxAge--;
	if(age==minAge)
		minAge++;
	newcount=count;
	while(array[age][i]!=-1){
		array[age][i]=-1;
		i++;
		count--;
	}
	return newcount;
}
/*
Inserts a new ID into the array sorted by the age passed to it either by createDataSet or main.
O(n) as the assignment said insertions would be infrequent.
Returns a custom data type to verify success in the UI.
 */
dubs insert(int age){//Simple function, includes some checks. O(n)
	dubs r;
	int j=0;
	if (age>31){
		r.cnt=-1;
		r.idnum=-1;
		return r;
	}
	if (count==3000){
			r.cnt=0;
			r.idnum=0;
			return r;
	}
	while(array[age][j]!=-1)
		j++;
	if (count==0){
		array[age][j]=rand()%(2+1-1);
		idtrack=array[age][j];
	}
	else{
		array[age][j]=(idtrack+rand()%(2+1-1)+1);
		idtrack=array[age][j];
	}
	if (age>maxAge)
		maxAge=age;
	if(age<minAge)
		minAge=age;
	count++;
	r.idnum=idtrack;
	r.cnt=count;
	return r;
}
/*
Searches for the IDs in an age group, made the assumption it should print them all.
O(n)
Void function, but it prints all the ID's
   */
void searchage(int age){//Another simple function. I assume we are to print the IDs in the age group. O(n)
	int i=0;//If we were supposed to print simply the number of students in the age group, I would add a column in my array that retains an individual counter.
	int check=0;//If we were to do that, or just simply check if there are students in the age group I would have a runtime of O(1).
	while(array[age][i]!=-1){
		if (check==0){
			printf("ID's in Age group entered:\n");
			check++;}
		printf("%d\t",array[age][i]);
		i++;
	}
	if(check==0)
		printf("No age matches\n");
}
/*
Uses the global variables to calculate the max age gap.
O(1)
Returns this value to the main for the benefit of the UI
   */
int maxage(){ //Big O(1). Could be altered easily if the ahge parameters were different.
	return(maxAge-minAge);
}

