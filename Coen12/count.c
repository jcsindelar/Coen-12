#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_WORD_LENGTH 30
//All the inclusions

//Joseph Sindelar

//No global variables since it is all in main

//Main function
int main(int argc, char *argv[])
{
	int counter=0;
	//Check for ARG error
	if (argc<2)
	{
		printf("Error in ARG");
		return 0;
	}
	char string[MAX_WORD_LENGTH+1];
	FILE *fp = fopen(argv[1], "r");
	//Check for text in file
	if (fp==NULL)
	{
		printf("Error in file length");
		return 0;
	}
	//Count the words
	while (fscanf(fp, "%s", string)==1) 
		counter++;
	printf("%d total words.\n", counter);
	return 0;
}


