#include <stdio.h>

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

//function prototypes
void questionA(customer);
void questionB(customer *);
void questionC(customer);
void questionD(customer *);
void questionE(customer);
void questionF(customer *);
//void questionG(customer);

int main()
{

	customerPtr = &customerRecord;

	questionA(customerRecord);
	questionB(customerPtr);
	questionC(customerRecord);
	questionD(customerPtr);
	questionE(customerRecord);
	questionF(customerPtr);
	//questionG(customerRecord);

	return 0;
}

void questionA(customer customerRecord)
{
	/*
	printf("customerRecord.lastName: ");
	for (int i = 0; i < 15; ++i)
	{
		printf("%c",customerRecord.lastName[i]);
	}
	printf("\n");
	*/
	printf("What would you like to change the last name to?\n");
	for (int j = 0; j < 14; ++j)
	{
		customerRecord.lastName[j] = getchar();
		if(customerRecord.lastName[j] == '\n')
		{
			customerRecord.lastName[j] = '\0';
			break;
		}
	}
	customerRecord.lastName[14] = '\0';

	printf("customerRecord.lastName: ");
	for (int k = 0; k < 15; ++k)
	{
		printf("%c",customerRecord.lastName[k]);
	}
	printf("\n\n");
}

void questionB(customer *customerPtr)
{
	printf("What would you like to change the last name to?\n");
	for (int j = 0; j < 14; ++j)
	{
		customerPtr->lastName[j] = getchar();
		if(customerPtr->lastName[j] == '\n')
		{
			customerPtr->lastName[j] = '\0';
			break;
		}
	}
	customerPtr->lastName[14] = '\0';

	printf("customerPtr->lastName: ");
	for (int k = 0; k < 15; ++k)
	{
		printf("%c",customerPtr->lastName[k]);
	}
	printf("\n\n");
}

void questionC(customer customerRecord)
{
	printf("What would you like to change the first name to?\n");
	for (int j = 0; j < 14; ++j)
	{
		customerRecord.firstName[j] = getchar();
		if(customerRecord.firstName[j] == '\n')
		{
			customerRecord.firstName[j] = '\0';
			break;
		}
	}
	customerRecord.firstName[14] = '\0';

	printf("customerRecord.firstName: ");
	for (int k = 0; k < 15; ++k)
	{
		printf("%c",customerRecord.firstName[k]);
	}
	printf("\n\n");
}

void questionD(customer *customerPtr)
{
	printf("What would you like to change the first name to?\n");
	for (int j = 0; j < 14; ++j)
	{
		customerPtr->firstName[j] = getchar();
		if(customerPtr->firstName[j] == '\n')
		{
			customerPtr->firstName[j] = '\0';
			break;
		}
	}
	customerPtr->firstName[14] = '\0';

	printf("customerPtr->firstName: ");
	for (int k = 0; k < 15; ++k)
	{
		printf("%c",customerPtr->firstName[k]);
	}
	printf("\n\n");
}

void questionE(customer customerRecord)
{
	/*
	printf("customerRecord.customerNumber: ");
	printf("%d",customerRecord.customerNumber);
	printf("\n");
	*/

	printf("What would you like to change customerNumber to?\n");
	scanf("%d",&customerRecord.customerNumber);

	printf("customerRecord.customerNumber: ");
	printf("%d",customerRecord.customerNumber);
	printf("\n\n");
}

void questionF(customer *customerPtr)
{
	printf("What would you like to change customerNumber to?\n");
	scanf("%d",&customerPtr->customerNumber);

	printf("customerPtr->customerNumber: ");
	printf("%d",customerPtr->customerNumber);
	printf("\n\n");
}

/*
void questionG(customer customerRecord)
{

	printf("What would you like to change the phone number to?\n");
	for (int j = 0; j < 11; ++j)
	{
		customerRecord.personal.phoneNumber[j] = getchar();
		if(customerRecord.personal.phoneNumber[j] == '\n')
		{
			customerRecord.personal.phoneNumber[j] = '\0';
			break;
		}
	}
	customerRecord.personal.phoneNumber[11] = '\0';

	printf("customerRecord.personal.phoneNumber: ");
	for (int k = 0; k < 11; ++k)
	{
		printf("%c",customerRecord.personal.phoneNumber[k]);
	}
	printf("\n\n");
}
*/
