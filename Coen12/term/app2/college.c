#include <stdio.h>
#include <stdlib.h>
#include "dataset.c"
// Joseph Sindelar
int main();

//Again didn't know we were allowed to have a header
//Also making the assumption you read comments in app1
int main(){
	int id, age;
	int maxb;
	int option;
	int check;
	int maxstud;
	dubs chk;
	while(1){//Included a switch to make the UI nicer.
		printf("\n1 for create DataSet\n 2 for destroy DataSet\n 3 to Search an ID\n 4 to delete entry\n 5 to quit\n");
		scanf("%d",&option);
		switch (option){
			case 1://Generates 1000 values
				maxstud=3000;
				createDataSet(3000);
				break;
			case 2://Destroys all values
				check=destroyDataSet();
				printf("Archives destroyed, students enrolled %d\n",check);
				break;
			case 3://Searches for a specific ID
				printf("Enter ID to search\n");
				scanf("%d",&id);
				check=searchid(id);
				if (check==0)
					printf("ID Not found\n");
				else
					printf("ID found\n");
				break;
			case 4://Removes a specific ID
				printf("Enter ID for removal\n");
				scanf("%d",&id);
				check=delete(id);
				if (check==0)
					printf("ID not found\n");
				else
					printf("Success!%d students enrolled now\n",check);
				break;
			case 5://Ends the program
				return 1;
			default:
				printf("Invalid Entry\n");
		}
	}
}

