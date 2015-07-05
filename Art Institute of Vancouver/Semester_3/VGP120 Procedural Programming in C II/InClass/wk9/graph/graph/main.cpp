#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//-------------------------------------

//function prototypes
int** CreateGraph(int&);
int** FillGraph(int**, const int);
void DisplayGraph(int**, const int);
void Instruction(int**, const int);
int Path(int**, const int);
int FindRandomIndirectPath(int**, const int, const int, const int);
void FreeMemory();

//-------------------------------------

int main()
{
	srand((unsigned)time(NULL));

	int cities = -1;
	int** pWorld = CreateGraph(cities);
	pWorld = FillGraph(pWorld, cities);
	DisplayGraph(pWorld, cities);
	Instruction(pWorld, cities);
	FreeMemory();

	return 0;
}

//-------------------------------------


int** CreateGraph(int& cities)
{
	cities = -1;
	while(cities < 1)
	{
		printf("How many cities are there?\n");
		scanf("%d" ,&cities);
		if(cities < 1)
		{
			printf("There must be at least 1 city.\n");
		}
	}

	int** pWorld = (int**)malloc(sizeof(int*)*cities);
	for(int i = 0; i < cities; ++i)
	{
		pWorld[i] = (int*)malloc(sizeof(int)*cities);
	}

	return pWorld;
}




int** FillGraph(int** pWorld, const int kCities)
{
	for(int source = 0; source < kCities; ++source)
	{
		for(int destination = 0; destination < kCities; ++destination)
		{
			if(source == destination)
			{
				pWorld[source][destination] = 0;
			}
			else
			{
				if(rand() % 2)//50% chance of a road existing
				{
					pWorld[source][destination] = rand() % 100 - 1;//road cost
				}
				else
				{
					pWorld[source][destination] = -1;//road doesn't exist
				}
			}
		}
	}

	return pWorld;
}




void DisplayGraph(int** pGraph, const int kCities)
{
	for(int source = 0; source < kCities; ++source)
	{
		for(int destination = 0; destination < kCities; ++destination)
		{
			printf("%d\t", pGraph[source][destination]);
		}
		printf("\n");
	}
}




void Instruction(int** pGraph, const int kCities)
{
	int choice = -1;
	int pathCost;
	while(choice == -1)
	{
		while(choice < 0)
		{
			printf("Would you like to query a path?\n");
			printf("1 for yes, 0 for no.\n");
			scanf("%d", &choice);
			if(choice < 0)
			{
				printf("You have entered and invalid input.\n");
			}
		}
		switch(choice)
		{
			case 0:
				printf("Bye!\n");
				break;
			case 1:
				{
					pathCost = Path(pGraph, kCities);
					if(pathCost > 0)
					{
						printf("The distance is %d.\n", pathCost);
					}
					else if(pathCost = 0)
					{
						printf("You are attempting from a location to itself. Distance = 0.\n");
					}
					else
					{
						printf("No path exists between these two locations.\n");
					}
					choice = -1;
					break;
				}
			default:
				printf("ERROR: Invalid choice given. No decision available in Instruction function. Terminating program. !!!\n");
				break;
		}
	}
	
}




int Path(int** pGraph, const int kCities)
{
	int source = -1;
	int destination = -1;

	while(source < 1)
	{
		printf("There are %d cities.\n", kCities);
		printf("Enter a source city.\n");
		scanf("%d", &source);
		if(source < 1)
		{
			printf("You have entered an invalid value.\n");
			printf("Please enter a new value.\n");
		}
		else if(source > kCities)
		{
			printf("There are only %d cities. Please enter a smaller value.\n", kCities);
		}
	}
	while(destination < 1)
	{
		printf("There are %d cities.\n", kCities);
		printf("Enter a destination city.\n");
		scanf("%d", &destination);
		if(destination < 1)
		{
			printf("You have entered an invalid value.\n");
			printf("Please enter a new value.\n");
		}
		else if(destination > kCities)
		{
			printf("There are only %d cities. Please enter a smaller value.\n", kCities);
		}
	}

	//path to self
	if(source == destination)
	{
		return 0;
	}

	//direct path
	if(pGraph[source][destination] > -1)
	{
		return pGraph[source][destination];
	}

	//no direct path, potential long path
	if(pGraph[source][destination] == -1)
	{
		return FindRandomIndirectPath(pGraph, source, destination, kCities);
	}

}




int FindRandomIndirectPath(int** pGraph, const int source, const int destination, const int kCities)
{
	int pathCost;
	bool visited[kCities];

	return pathCost;
}




void FreeMemory()
{

}