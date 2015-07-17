//#include <stdio.h>
//
//
//
//int length(char list[])
//{
//
//	int counter = 0;
//
//	for(int i = 0; i > -1; i++)
//	{
//		if(list[i]!=NULL)
//		{
//			counter++;
//		}
//		else
//		{
//			counter++;
//			break;
//		}
//	}
//
//
//
//	return counter;
//
//}
//
//
//
//
//int main()
//{
//
//	char name[] = {'V','G','P',NULL};
//	int d;
//
//	d = length(name);
//
//	printf("The length of the array is: %d\n",d);
//
//	return 0;
//
//}





//#include <stdio.h>
//
//int main()
//{
//
//
//	char input[20];
//	printf("Please enter a string of stuff 19 characters or less.\n");
//	scanf("%s",&input);
//	printf("%s\n",input);
//
//
//	return 0;
//
//}






#include <stdio.h>


void inputString (char input[], int length)
{

	int i;
	char c;

	for(i = 0; i < length-1; i++)
	{
		c=getchar();
		if(c=='\n')
		{
			break;
		}
		input[i]=c;
	}

	input[i]=NULL;

	return;

}




void main()
{

	char input[20];
	
	//scanf("%s",&input);

	inputString(input,20);

	printf("%s\n",input);



}

