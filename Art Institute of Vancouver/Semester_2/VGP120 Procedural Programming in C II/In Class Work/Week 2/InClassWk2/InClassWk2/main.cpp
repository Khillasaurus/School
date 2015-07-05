#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void alphabeticalize(char *, char *);
void checkValidity(char *, int);

int main()
{
	char s1[100];
	char *s1Ptr = &s1[0];
	char s2[100];
	char *s2Ptr = &s2[0];
	int stringNum = 1;

	alphabeticalize(s1Ptr, s2Ptr);

	printf("\n");

	checkValidity(s1Ptr, stringNum);
	++stringNum;
	checkValidity(s2Ptr, stringNum);

	return 0 ;
}

void alphabeticalize(char *s1Ptr, char *s2Ptr)
{
	printf("Please enter 2 strings less than 100 characters seperated by a new line.\n");
	scanf("%s%s", s1Ptr, s2Ptr);
	printf("\nThe strings you entered in alphabetical order is: \n");

	if (strcmp(s1Ptr, s2Ptr)<1)
	{
		printf("%s\n%s\n", s1Ptr, s2Ptr);
	}
	else
	{
		printf("%s\n%s\n", s2Ptr, s1Ptr);
	}
}

void checkValidity(char *Ptr, int stringNum)
{
	if ((strchr(Ptr, '@') != NULL) && (strchr(Ptr, '.') != NULL))
	{
		printf("String %d is a valid e-mail address.\n", stringNum);
	}
	else
	{
		printf("String %d is not a valid e-mail address.\n", stringNum);
	}
}