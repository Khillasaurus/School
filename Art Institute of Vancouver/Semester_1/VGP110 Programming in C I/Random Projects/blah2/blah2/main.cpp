/* Fig. 8.9: fig08_09.c
   Using strtod */
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int main( void )
{ 
	/* initialize string pointer */
	char string[] = "asdfsdfsadf 51.2% are admitted"; /* initialize string */

	int i = 0;
	double d;        /* variable to hold converted sequence */
	char *stringPtr = string; /* create char poitner */
	char *sPtr2;
	char list[100];

	for(i = 0; i < (sizeof(string)/sizeof(char)); i++)
	{
		if(isdigit(string[i]) != 0)
		{
			break;
		}
		list[i] = string[i];
	}
	list[i] = '\0';

	for(int j = 0; j < (sizeof(string)/sizeof(char)); j++)
	{
		if(isdigit(string[j]) == 0)
		{
			stringPtr++;
			//d = strtod( string, &string2Ptr );
		}
		else
		{
			break;
		}
	}

	d = strtod( stringPtr, &sPtr2 );

	printf( "The string \"%s\" is converted to the\n", string );
	printf( "first part of string: ");
		//for(int k = 0; list[k]!='\0'; k++)
		//{
			printf("%s",list);
		//}
		printf(" double value: %.2f second part of string: \"%s\"\n", d, sPtr2 );

	return 0; /* indicates successful termination */

} /* end main */

