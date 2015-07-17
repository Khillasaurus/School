#include <stdio.h>

int main()
{
	const int size = 10;
	int studentNumberList[size];
	int scoresList1[size];
	int scoresList2[size];
	int list1Average = 0;
	int list2Average = 0;
	
	FILE *cfPtr;//cfPtr = data.txt file pointer

	//fopen opens file. Exit program if unable to create file
	if((cfPtr = fopen("C:\\Users\\212395\\Desktop\\wk3\\inClass2\\inClass2\\data.txt", "r")) == NULL)
	{
		printf("File could not be opened\n");
	}//end if
	else
	{
		for (int j = 0; j < size; ++j)
		{
			fscanf(cfPtr, "%d%d%d", &studentNumberList[j], &scoresList1[j], &scoresList2[j]);
			printf("%d\t%d\t%d\n", studentNumberList[j], scoresList1[j], scoresList2[j]);
		}
		fclose(cfPtr);//fclose closes file
	}//end else

	for(int k = 0; k < size; ++k)
	{
		list1Average += scoresList1[k];
		list2Average += scoresList2[k];
	}
	list2Average *= 2;
	list1Average /= size;
	list2Average /= size;

	printf("The average score for test 1 is: %d\n", list1Average);
	printf("The average score for test 2 is: %d\n", list2Average);
	printf("The average score for the tests combined is: %d\n", (list1Average+list2Average)/2);

	return 0;
}