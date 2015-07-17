#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
	//initialize random seed:
	srand (time(NULL));

	int amountOfStudents;
	int** studentNumberPtr;
	int amountOfData = 2;//id and gpa
	int amountOf4GPAs = 0;

	printf("Please enter how many id's you would like to enter: ");
	scanf("%d", &amountOfStudents);
	printf("\n");

	studentNumberPtr = (int**)malloc(sizeof(int*) * amountOfStudents);

	for ( int i = 0; i < amountOfStudents; ++i )
	{
		*(studentNumberPtr+i) =  ( (int*)malloc(sizeof(int) * amountOfData) );
		studentNumberPtr[i][0] = rand() % 1001 + 999 ;
		studentNumberPtr[i][1] = rand() % 5 ;
	}

	for ( int j = 0; j < amountOfStudents; ++j )
	{
		printf("Student Number: %d\t\tID: %d\t\tGPA: %d\n", j+1, studentNumberPtr[j][0], studentNumberPtr[j][1]);
	}

	printf("\n");
	//search for 4.0 GPA's
	for ( int k = 0; k < amountOfStudents; ++k )
	{
		if ( studentNumberPtr[k][1] == 4 )
		{
			printf("Student Number %d with ID %d has earned a perfect 4 GPA.\n", k+1, studentNumberPtr[k][0]);
			++amountOf4GPAs;
		}
	}
	printf("\nThe amount of GPA's with score 4 is: %d\n", amountOf4GPAs);

	free ( studentNumberPtr );

	return 0;
}