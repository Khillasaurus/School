#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void display(int** , int );
void seating(int** , int , int );

int main()
{
	//initialize random seed:
	srand (time(NULL));

	int seats = 0;
	int seatingClass = -1;
	int** seatsPtr;
	int firstClassFilled = 0;
	int economyClassFilled = 0;
	int switchClass;

	printf("How many seats are there in each row?\n");
	scanf("%d", &seats);

	seatsPtr = (int**)malloc(sizeof(int*) * seats);

	while(seatingClass!=0)
	{
		printf("Please enter a 1 for \"first class\".\n");
		printf("Please enter a 2 for \"economy\".\n");
		printf("Please enter a 0 to quit.\n");
		scanf("%d",&seatingClass);


		if(seatingClass==0)
		{
			break;
		}

		if(seatingClass==1)
		{
			firstClassFilled++;
			if(firstClassFilled>seats)
			{
				printf("First class is full. Would you like to sit in the economy class?\n");
				printf("Enter a 1 for yes or a 0 for no.\n");
				scanf("%d",&switchClass);
				if(switchClass==0)
				{
					printf("Next Flight leaves in 3 hours.\n");
					break;
				}
				else
				{
					seatingClass = 2;
				}
			}
		}

		if(seatingClass==2)
		{
			economyClassFilled++;
			if(economyClassFilled>seats && firstClassFilled<seats)
			{
				printf("Economy class is full. Would you like to sit in the first class?\n");
				printf("Enter a 1 for yes or a 0 for no.\n");
				scanf("%d",&switchClass);
				if(switchClass==0)
				{
					printf("Next Flight leaves in 3 hours.\n");
					break;
				}
				else
				{
					seatingClass = 1;
					firstClassFilled++;
				}
			}
			if(firstClassFilled>seats && economyClassFilled>seats)
			{
				printf("Next Flight leaves in 3 hours.\n");
				break;
			}
		}

		seating(seatsPtr, seatingClass, seats);
		display(seatsPtr, seats);
	}

	return 0;
}


void display(int** seatsPtr, int seats)
{
	for(int i = 0; i < seats; i++)
	{
		if(i==0)
		{
			printf("First Class:\t%d",seatsPtr[i]);
		}
		else if(i==(seats/2))
		{
			printf("\nEconomy:\t%d",seatsPtr[i]);
		}
		else if(i==(seats-1))
		{
			printf("%d\n\n",seatsPtr[i]);
		}
		else
		{
			printf("%d",seatsPtr[i]);
		}
	}
}




void seating(int** seatsPtr, int seatingClass, int seats)
{
	bool seatedProperly = false;
	int seatNumber;

	while(seatedProperly==false)
	{
		//generate secret number from 0 to seats
		seatNumber = rand() % seats;
		if(seatingClass==2)
		{
			seatNumber += seats;
		}

		if(seatsPtr[seatNumber]==0)
		{
			*seatsPtr[seatNumber]=1;
			seatedProperly=true;
		}
		else
		{
			seatNumber = rand() % seats;
		}
	}
}
