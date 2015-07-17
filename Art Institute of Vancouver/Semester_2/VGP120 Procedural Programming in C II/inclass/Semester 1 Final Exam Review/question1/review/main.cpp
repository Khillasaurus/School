#include <stdio.h>
//#include <ctype.h>
//#include <string.h>
#include <stdlib.h>

float Round(float,int);

int main()
{

	char temp[100];
	double f;
	int digits = 0;
	float num = 12.545;

	sprintf(temp, "%.*f", digits, num);

	//printf("%s",temp);

	f = atof(temp);

	printf("%.*f\n", digits, f);
	//printf("%f\n%f",f,num);

	return 0;

}