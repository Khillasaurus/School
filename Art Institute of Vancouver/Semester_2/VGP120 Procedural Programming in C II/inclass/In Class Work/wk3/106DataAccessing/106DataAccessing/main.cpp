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

	return 0;
}