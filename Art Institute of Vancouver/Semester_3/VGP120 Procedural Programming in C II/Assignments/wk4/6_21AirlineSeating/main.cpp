#include <stdio.h>
#include <stdlib.h>

//function prototypes
void InitializeSeats(int*, const int);
void DisplaySeats(int*, const int, const int);
bool FillSeats(bool &, int*, const int, const int);
void PlaceInSeat(bool &, int*, int, const int, const int, int*);
bool IsFull(int*, const int);

int main()
{
	int totalSeats = 0;
	float firstClassPercentage = -1;
	int firstClassSeats = 0;
	int economyClassSeats = 0;
	bool flightFull = false;

	while(totalSeats <= 0)
	{
		printf("How many seats are there in the airplane?\n");
		scanf("%d", &totalSeats);
		if(totalSeats <= 0)
		{
			printf("There must be atleast one seat on the airplane.\n");
		}
	}
	while(firstClassPercentage < 0 || firstClassPercentage > 100)
	{
		printf("What percentage of seats are first class?\n");
		scanf("%f", &firstClassPercentage);
		if(firstClassPercentage < 0 || firstClassPercentage > 100)
		{
			printf("The percentage of first class seats must be between 0 and 100 inclusive.\n");
		}
	}
	firstClassPercentage /= 100;
	firstClassSeats = totalSeats * firstClassPercentage;
	economyClassSeats = totalSeats - firstClassSeats;
	printf("\n");

	int* seatsPtr = (int*)malloc(totalSeats * sizeof(int));//using single-subscripted array to represent a 2 line problem
	if(seatsPtr == NULL)
	{
		printf("Insufficient memory to run program.\n");
	}
	else
	{
		InitializeSeats(seatsPtr, totalSeats);
		flightFull = IsFull(seatsPtr, totalSeats);
		while(!flightFull)
		{
			if(FillSeats(flightFull, seatsPtr, firstClassSeats, totalSeats))//if true user wants to quit
			{
				printf("Bye!\n");
				break;
			}
		}
		free(seatsPtr);
		seatsPtr = NULL;
	}

	return 0;
}




void InitializeSeats(int* seatsPtr, const int totalSeats)
{
	for(int i = 0; i < totalSeats; ++i)
	{
		seatsPtr[i] = 0;//0 for empty seat, 1 for full seat
	}
}




void DisplaySeats(int* seatsPtr, const int totalSeats, const int firstClassSeats)
{
	printf("1 signifies a taken seat while 0 signifies an empty seat.\n");
	printf("First Class:\t\t");
	for(int i = 0; i < totalSeats; ++i)
	{
		printf("%d", seatsPtr[i]);
		if(i == firstClassSeats)
		{
			printf("\nEconomy Class:\t\t");
		}
	}
	printf("\n");
}




bool FillSeats(bool &flightFull, int* seatsPtr, const int firstClassSeats, const int totalSeats)
{
	int classChoice = 0;
	int quit = 0;
	int* emptyPtr = (int*)malloc(sizeof(int));

	while(!flightFull)
	{
		DisplaySeats(seatsPtr, totalSeats, firstClassSeats);
		
		while(quit < 1 || quit > 2)
		{
			printf("Would you like to quit?\n");
			printf("1 for yes or 2 for no.\n");
			scanf("%d", &quit);
			if(quit < 1 || quit > 2)
			{
				printf("You have entered an invalid choice.\n");
			}
		}
		if(quit == 1)
		{
			return true;
		}

		while(classChoice < 1 || classChoice > 2)
		{
			printf("Where would you like to sit?\n");
			printf("Enter 1 for first class.\n");
			printf("Enter 2 for economy class.\n");
			scanf("%d", &classChoice);
			if(classChoice < 1 || classChoice > 2)
			{
				printf("You have entered an invalid choice.\n");
			}
		}
		
		PlaceInSeat(flightFull, seatsPtr, classChoice, firstClassSeats, totalSeats, emptyPtr);
	}

	return false;
}




void PlaceInSeat(bool &flightFull, int* seatsPtr, int classChoice, const int firstClassSeats, const int totalSeats, int* emptyPtr)
{
	int resize = 0;
	int decision = 0;
	int seatChoice = 0;
	bool validChoice = false;
	int compensation = 0;

	while(!flightFull)
	{
		printf("The following seats are empty in that section:\n");

		if(classChoice == 1)
		{
			for(int i = 0; i < firstClassSeats; ++i)
			{
				if(seatsPtr[i] == 0)
				{
					++resize;
				}
			}
		}
		else
		{
			for(int i = firstClassSeats+1; i < totalSeats; ++i)
			{
				if(seatsPtr[i] == 0)
				{
					++resize;
				}
			}
		}

		if(resize == 0)
		{
			printf("There are no seats available in ");
			if(classChoice == 1)
			{
				printf("first class.\n");
			}
			else
			{
				printf("economy class.\n");
			}

			printf("Would you like to sit in ");
			if(classChoice == 1)
			{
				printf("economy class?\n");
			}
			else
			{
				printf("first class?\n");
			}

			while(compensation < 1 || compensation > 2)
			{
				printf("1 for yes or 2 for no.\n");
				scanf("%d", &compensation);
				if(compensation < 1 || compensation > 2)
				{
					printf("You have entered an invalid choice.\n");
				}
			}

			if(compensation == 1)
			{
				if(classChoice == 1)
				{
					classChoice = 2;
				}
				else
				{
					classChoice = 1;
				}
			}
			else
			{
				printf("Next flight leaves in 3 hours.\n");
				flightFull = true;	/*even though the flight isn't full this is required in order to
									break out of loops in other functions to terminate the program*/
				break;
			}
		}

		if(compensation == 1)
		{
			if(classChoice == 1)
			{
				for(int i = 0; i < firstClassSeats; ++i)
				{
					if(seatsPtr[i] == 0)
					{
						++resize;
					}
				}
			}
			else
			{
				for(int i = firstClassSeats+1; i < totalSeats; ++i)
				{
					if(seatsPtr[i] == 0)
					{
						++resize;
					}
				}
			}
		}

		if(resize == 0)
		{
			printf("Flight full. Next flight leaves in 3 hours.\n");
			flightFull = true;
			break;
		}

		seatsPtr = (int*)realloc(emptyPtr, resize * sizeof(int));
		int* tempPtr = emptyPtr;//shallow copy

		if(classChoice == 1)
		{
			for(int i = 0; i < firstClassSeats; ++i)
			{
				if(seatsPtr[i] == 0)
				{
					*tempPtr = i;
					++tempPtr;
				}
			}
		}
		else
		{
			for(int i = firstClassSeats+1; i < totalSeats; ++i)
			{
				if(seatsPtr[i] == 0)
				{
					*tempPtr = i;
					++tempPtr;
				}
			}
		}

		for(int i = 0; i < resize; ++i)
		{
			printf("%d, ", emptyPtr[i]);
		}
		printf("\n");

		while(decision < 1 || decision > 2)
		{
			printf("Would you like to sit here?\n");
			printf("1 for yes or 2 for no.\n");
			scanf("%d", &decision);
			if(decision < 1 || decision > 2)
			{
				printf("You have entered an invalid choice.\n");
			}
		}
		if(decision == 1)
		{
			while(!validChoice)
			{
				printf("Which seat would you like to sit in?");
				scanf("%d", &seatChoice);
				for(int i = 0; i < resize; ++i)
				{
					if(seatChoice == emptyPtr[i])
					{
						emptyPtr[i] = 1;
						validChoice = true;
					}
					else
					{
						printf("You have entered an invalid choice. Please choose again.\n");
						printf("The following seats are empty in that section:\n");
						for(int i = 0; i < resize; ++i)
						{
							printf("%d, ", emptyPtr[i]);
						}
						printf("\n");
					}
				}
			}

		}
		
		free(emptyPtr);
		emptyPtr = NULL;
		tempPtr = NULL;
	}//end of while(!flightFull)
}




bool IsFull(int* seatsPtr, const int totalSeats)
{
	for(int i = 0; i < totalSeats; ++i)
	{
		if(seatsPtr[i] == 0)
		{
			return false;
		}
	}
	return true;
}