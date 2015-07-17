#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define NUM_ACCOUNTS 100

void initializeAccounts(int *);
void displayAccounts(int *, float*, float *, int);
void deposit(int *, int);
void withdraw(int *, int);
void calculateInterest(int *, float *, float *);//calculates interest of all accounts
void calculateInterest(int *, float*, float *, int);//calculate interest of 1 specific account
void generateInterest(float *);//Between 0.00 and 6.99

int main()
{
	int accounts[100];
	float interestRate[100];
	float interestAmmount[100];
	int *aPtr = &accounts[0];
	float *irPtr = &interestRate[0];
	float *iaPtr = &interestAmmount[0];
    srand(time(NULL));
	int accountNum = 0;

	initializeAccounts(aPtr);
	generateInterest(irPtr);
	calculateInterest(aPtr, irPtr, iaPtr);
	for(int j = 0; j < 100; j++)
	{
		displayAccounts(aPtr, irPtr, iaPtr, accountNum);
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

	return;
}

void displayAccounts(int *aPtr, float *irPtr, float *iaPtr, int accountNum)
{
	int choice = 0;

	printf("Account#: %d\n",accountNum+1);
	printf("\tBalance:\t%d\n",*(aPtr+accountNum));
	printf("\tInterest Rate:\t%.2f\n",*(irPtr+accountNum));
	printf("\tInterest:\t%.2f\n",*(iaPtr+accountNum));

	printf("Select one of the following options:\n");
	printf("1 - Deposit\n");
	printf("2 - Withdraw\n");
	printf("3 - Done\n");
	scanf("%d",&choice);
    while(choice<1 || choice >3)
    {
        printf("You have entered an invalid option. Please choose again.\n");
        printf("Please select one of the following options:\n");
        printf("1 - Deposit\n");
        printf("2 - Withdraw\n");
        printf("3 - Done\n");
        scanf("%d",&choice);
    }

    if(choice==1)
    {
        deposit(aPtr, accountNum);
        calculateInterest(aPtr, irPtr, iaPtr, accountNum);

        printf("Account#: %d\n",accountNum+1);
        printf("\tBalance:\t%d\n",*(aPtr+accountNum));
        printf("\tInterest Rate:\t%.2f\n",*(irPtr+accountNum));
        printf("\tInterest:\t%.2f\n",*(iaPtr+accountNum));
    }
    else if(choice==2)
    {
        withdraw(aPtr, accountNum);
        calculateInterest(aPtr, irPtr, iaPtr, accountNum);

        printf("Account#: %d\n",accountNum+1);
        printf("\tBalance:\t%d\n",*(aPtr+accountNum));
        printf("\tInterest Rate:\t%.2f\n",*(irPtr+accountNum));
        printf("\tInterest:\t%.2f\n",*(iaPtr+accountNum));
    }
    else
    {
        printf("Account#: %d\n",accountNum+1);
        printf("\tBalance:\t%d\n",*(aPtr+accountNum));
        printf("\tInterest Rate:\t%.2f\n",*(irPtr+accountNum));
        printf("\tInterest:\t%.2f\n",*(iaPtr+accountNum));
    }

	return;
}

void generateInterest(float *irPtr)
{
    int beforeDecimal = 0;
    float afterDecimal = 0;
    float finalValue = 0;

    for(int i = 0; i < 100; i++)
    {

        beforeDecimal = rand()%7;
        afterDecimal = rand()%100;
        afterDecimal = (afterDecimal/100);
        finalValue = beforeDecimal + afterDecimal;

        *irPtr = finalValue;
		irPtr++;
    }

    return;
}

void calculateInterest(int *aPtr, float *irPtr, float *iaPtr)
{
    for(int i = 0; i < 100; i++)
	{
		*iaPtr = *aPtr * (*irPtr/100);
        aPtr++;
        irPtr++;
        iaPtr++;
	}

    return;
}

void calculateInterest(int *aPtr, float *irPtr, float *iaPtr, int accountNum)
{
    aPtr += accountNum;
    irPtr += accountNum;
    iaPtr += accountNum;
    *iaPtr = *aPtr * (*irPtr/100);

    return;
}

void deposit(int *aPtr, int accountNum)
{
    int amount = 0;
    aPtr += accountNum;

    printf("How much would you like to deposit in whole dollars only?\n\t");
    scanf("%d",&amount);

        *aPtr += amount;

    return;
}

void withdraw(int *aPtr, int accountNum)
{
    int amount = 0;
    aPtr += accountNum;

    printf("How much would you like to withdraw in whole dollars only?\n\t");
    scanf("%d",&amount);

    if((*aPtr-amount)<0)
    {
        printf("Sorry, withdrawal amount exceeds allowed limits!\n");
    }
    else
    {
        *aPtr -= amount;
    }

    return;
}
