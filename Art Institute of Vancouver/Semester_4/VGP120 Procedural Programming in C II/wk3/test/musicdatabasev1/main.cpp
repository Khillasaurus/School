//----------------------------------
// File:		main.cpp
// Created:		2012/04/22
// Copyright:	Daniel Schenker
//----------------------------------

#include <stdio.h>

//Function Prototypes
int InstructionsA();
int InstructionsB(bool*, const int);
void InstructionsC();
int Search();
void AddSong();
void Shuffle();
void Statistics();

int main()
{
	int choice = -2;

	printf("Welcome to Khillasaurus Music Player!\n");

	while(choice != -1)
	{
		choice = InstructionsA();
	}
	//close *.txt files
	
}

int InstructionsA()
{
	int choice = 0;
	printf("What would you like to do?\n");
	printf("1: Search for a song.\n");
	printf("2: Add a song.\n");
	printf("3: Shuffle.\n");
	printf("4: Statistics.\n");
	printf("-1: Quit.\n");

	scanf("%d", &choice);

	switch(choice)
	{
		case 1:
			choice = Search();
			break;
		case 2:
			AddSong();
			break;
		case 3:
			Shuffle();
			break;
		case 4:
			Statistics();
			break;
		case -1:
			return -1;
		default:
			printf("Invalid choice. Please choose again.\n");
			InstructionsA();
			break;
	}
	return choice;
}

int InstructionsB(bool* pNarrowOptions, const int kOptions)
{
	int choice = -2;
	int shouldRemove = -1;

	while((choice < -1) ||(choice > 12))
	{
		printf("How would you like to narrow your search results?\n");
		printf("1: Artist\n");
		printf("2: Song\n");
		printf("3: Album\n");
		printf("4: Tag\n");
		printf("5: Genre\n");
		printf("6: Plays\n");
		printf("7: Rating\n");
		printf("8: Length\n");
		printf("9: Additional Information\n");
		printf("10: Local Link\n");
		printf("11: Online Link\n");
		printf("12: Search in selected categories\n");
		printf("13: Search in all categories (will overide all previous choices)\n");
		printf("0: Return to main menu\n");
		printf("-1: Quit\n");

		scanf("%d", &choice);

		if((choice < -1) ||(choice > 13))
		{
			printf("Invalid choice given. Please choose again.\n");
		}
		else if((choice == -1) || (choice == 0))
		{
			return choice;
		}
		else if(pNarrowOptions[choice - 1] == true)
		{
			while((shouldRemove != 1) || (shouldRemove != 0))
			{
				printf("That option is already chosen. Would you like to remove it? 1 for yes, 0 for no.\n");
				scanf("%d", &shouldRemove);
				if((shouldRemove != 1) || (shouldRemove != 0))
				{
					printf("Invalid choice given. Please choose again.\n");
				}
				else if(shouldRemove == 1)
				{
					pNarrowOptions[choice - 1] = false;
				}
			}

		}
		else if(choice == 12)
		{
			pNarrowOptions[choice - 1] = true;
			return choice;
		}
		else if(choice == 13)
		{
			for(int i = 0; i < kOptions; ++i)
			{
				pNarrowOptions[i] = true;
			}
			return choice;
		}
		else
		{
			pNarrowOptions[choice - 1] = true;
		}
	}

	return choice;
}

int Search()
{
	const int kOptions = 13;
	int storage = -2;
	bool narrowOptions[kOptions] = {false};
	bool* pNarrowOptions = &narrowOptions[0];

	for(int i = 0; ((storage != -1) || (storage != 0)); ++i)
	{
		storage = InstructionsB(pNarrowOptions, kOptions);
		if((storage == -1) || (storage == 0))
		{
			return storage;
		}
		if(narrowOptions[i] == 12)
		{
			//stop searching and display results
		}
		else
		{
			if(narrowOptions[i])
			{
				//search
			}
		}
	}

	//These two lines of code are simply to allow testing. Should be changed later on.
	return 0;
	InstructionsC();
}

void InstructionsC()
{
}

void AddSong()
{
}

void Shuffle()
{
}

void Statistics()
{
}