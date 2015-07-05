#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
	int studentNumber = 1;
	const int size = 10;
	int testScore1[size];
	int testScore2[size];

	//initialize random seed:
	srand (time(NULL));

	//generate test scores
	for (int i = 0; i < size; ++i)
	{
		testScore1[i] = rand() % 101;
		testScore2[i] = rand() % 51;
	}
	
	FILE *cfPtr;//cfPtr = data.txt file pointer

	//fopen opens file. Exit program if unable to create file
	if((cfPtr = fopen("data.txt", "w")) == NULL)
	{
		printf("File could not be opened\n");
	}//end if
	else
	{
		for (int j = 0; j < size; ++j)
		{
			fprintf(cfPtr, "%d\t%d\t%d\n", studentNumber, testScore1[j], testScore2[j]);
			++studentNumber;
		}
		fclose(cfPtr);//fclose closes file
	}//end else

	return 0;
}