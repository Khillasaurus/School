#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define NUM_ACCOUNTS 100

void initializeAccounts(int *);
void displayAccounts(int *, int);
void deposit(int *, int);//int amountDesposit
void withdraw(int *, int);//int amountWithdraw
void calculateInterest(int *, float);//float interestRate
float generateInterest();//Between 2.00 and 6.99

int main()
{

	int accounts[100];
	int *aPtr = &accounts[0];
	srand(time(NULL));
	int accountNum = 0;

	initializeAccounts(aPtr);
	for(int j = 0; j < 100; j++)
	{
		displayAccounts(aPtr, accountNum);
		accountNum++;
	}

	return 0;

}

void initializeAccounts(int *aPtr)
{
	for(int i = 0; i < 100; i++)
	{
		*aPtr = 1000 + rand()%9001;
		aPtr++;
	}
}

void displayAccounts(int *aPtr, int accountNum)
{
	printf("Account#: %d\n\tBalance: %d\n",accountNum,(aPtr+accountNum));
}
