#include <stdio.h>

int main()
{
	struct customer
	{
		char lastName[15];
		char firstName[15];
		int customerNumber;

		struct
		{
			char phoneNumber[11];
			char address[50];
			char city[15];
			char state[3];
			char zipCode[6];
		}personal;
	}customerRecord, *customerPtr;

	customerPtr = &customerRecord;


	printf("customerRecord.lastName: ");
	for (int i = 0; i < 15; ++i)
	{
		printf("%c",customerRecord.lastName[i]);
	}
	printf("\n");

	printf("What would you like to change the last name to?\n");
	for (int j = 0; j < 14; ++j)
	{
		customerRecord.lastName[j] = getchar();
	}
	customerRecord.lastName[14] = '\0';

	printf("customerRecord.lastName: ");
	for (int k = 0; k < 15; ++k)
	{
		printf("%c",customerRecord.lastName[k]);
	}
	printf("\n");

	return 0;
}
