#include <stdio.h>
#include <stdlib.h>
#include "dataset.c"
// Joseph Sindelar
int main();
//Did not know we were allowed to have a .h file in this project. I am not in the lab section this quarter and so there were a couple things that I was unclear on.
//Professor Liu said that due to the fact I am not in the lab section, and could not get my questions clarified before the due date that she would not hit me with a late penalty.
//She also added that if you need proof of this, I can email you and CC her on the email.

int main(){
	int id, age;//I was unclear what precisely needed to be in college.c and what needed to be in dataset.c, but my code works I think.
	int maxb;
	int option;
	int check;
	dubs chk;
	while(1){
		printf("\n1 for create DataSet\n 2 for destroy DataSet\n 3 to insert\n 4 to search for an Age Group\n 5 for max age gap\n 6 to delete entry\n 7 to quit\n");
		scanf("%d",&option);
		switch (option){//I understand now that we did not need a switch, so I apologize
			case 1:
				students=3000;
				createDataSet(students);//Generate 1000 students
				break;
			case 2:
				check=destroyDataSet();
				printf("Archives destroyed, students enrolled %d\n",check);//Should print 0
				break;
			case 3:
				printf("Enter Age\n");//Insert manually
				scanf("%d",&age);
				chk=insert(age);
				if(chk.cnt==-1)
					printf("Too old to enroll\n");//I am not sure if the age perameter needs to be included or not. See my dataset.c for more explanation.
				if (chk.cnt==0)
					printf("Classes full, try again in the fall\n");
				if(chk.cnt!=-1 && chk.cnt!=0)
					printf("Success! Your ID number is %d, and the current capacity is %d.\n",chk.idnum,chk.cnt);
				break;
			case 4:
				printf("Enter age to search\n");//Searches for all IDs
				scanf("%d",&age);
				searchage(age);
				break;
			case 5:
				maxb=maxage();//Prints max age gap
				printf("Max age gap is %d years.\n",maxb);
				break;
			case 6:
				printf("Enter Age Set for removal\n");//Removes all ID's with a given age
				scanf("%d",&age);
				check=delete(age);
				if (check==count)
					printf("Nothing to delete\n");
				else
					printf("Success!%d students enrolled now\n",count);
				break;
			case 7://Closes the program
				return 1;
			default:
				printf("Invalid Entry\n");
		}
	}
}

