#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//function prototypes
//---------------------------------------------------------------
void GenerateStudentInfo( struct student*, const unsigned int );
void SequentialWrite( struct student*, const unsigned int );
void UpdateInfo( struct student*, const unsigned int );
//---------------------------------------------------------------


//globals
//---------------------------------------------------------------
struct student
{
	unsigned int id;
	unsigned int test1;
	unsigned int test2;
};
//---------------------------------------------------------------


int main()
{
	const unsigned int kAmountOfStudents = 50;
	struct student list[kAmountOfStudents];
	struct student* listPtr = &list[0];
	int choice = 0;

	srand( (unsigned)time(NULL) );

	SequentialWrite( listPtr, kAmountOfStudents );
	while( choice >= 0 )
	{
		printf( "Enter 1 to edit test score(s). Enter -1 to quit.\n");
		scanf( "%d", &choice );
		if( choice >= 0 )
		{
			UpdateInfo( listPtr, kAmountOfStudents );
		}
	}

	return 0;
}

void GenerateStudentInfo( struct student* listPtr, const unsigned int kAmountOfStudents )
{
	for( int i = 0; i < kAmountOfStudents; ++i )
	{
		listPtr[i].id = rand() % 100 + 1;
		listPtr[i].test1 = rand() % 101;
		listPtr[i].test2 = rand() % 51;
	}
}

void SequentialWrite( struct student* listPtr, const unsigned int kAmountOfStudents )
{
	FILE *cfPtr;//cfPtr = marks.dat file pointer

	//fopen opens file. Exit program if unable to create file
	if( (cfPtr = fopen("marks.dat", "w")) == NULL )
	{
		printf( "File could not be opened\n" );
	}
	else
	{
		GenerateStudentInfo( listPtr, kAmountOfStudents );

		for( int i = 0; i < kAmountOfStudents; ++i )
		{
			fprintf( cfPtr, "%d\t\t%d\t\t%d\n", listPtr[i].id, listPtr[i].test1, listPtr[i].test2 );
		}	
		fclose( cfPtr );
	}
}

void UpdateInfo( struct student* listPtr, const unsigned int kAmountOfStudents )
{
	unsigned int idChoice = 0;
	unsigned int newTest1 = 0;
	unsigned int newTest2 = 0;

	unsigned int previousId;
	unsigned int previousTest1;
	unsigned int previousTest2;
	unsigned int currentId;
	unsigned int currentTest1;
	unsigned int currentTest2;
	unsigned int secondCurrentId;
	unsigned int secondCurrentTest1;
	unsigned int secondCurrentTest2;

	FILE *cfPtr;//cfPtr = marks.dat file pointer

	if( (cfPtr = fopen("marks.dat", "r+")) == NULL )
	{
		printf( "File could not be opened\n" );
	}
	else
	{
		while( idChoice < 1 || idChoice > 100 )
		{
			printf( "Which id would you like to edit?\n" );
			scanf( "%d", &idChoice );
			if( idChoice < 1 || idChoice > 100 )
			{
				printf( "Invalid id entered. Please enter a new id.\n" );
			}
		}
		
		//move file pointer to correct id
		while( !feof(cfPtr) )
		{
			//fscanf( cfPtr, "%d%d%d", &previousId, &previousTest1, &previousTest2 );
			fscanf( cfPtr, "%d%d%d", &currentId, &currentTest1, &currentTest2 );
			if( currentId == idChoice )
			{
				printf( "id: %d\t\ttest1: %d\t\ttest2: %d\n", currentId, currentTest1, currentTest2 );
				break;
			}
			
		}
		fseek( cfPtr, -(sizeof (struct student)), SEEK_CUR );
		printf( "What would you like the two new test scores to be?\n" );
		scanf( "%d%d", &newTest1, &newTest2 );
		fprintf( cfPtr, "\n%d\t\t%d\t\t%d\n", currentId, newTest1, newTest2 );

		/*
		rewind( cfPtr );//return cfPtr to beginning of file
		while( !feof(cfPtr) )
		{
			fscanf( cfPtr, "%d%d%d", &secondCurrentId, &secondCurrentTest1, &secondCurrentTest2 );
			if( secondCurrentId == previousId )
			{
				printf( "What would you like the two new test scores to be?\n" );
				scanf( "%d%d", &newTest1, &newTest2 );
				fprintf( cfPtr, "%d\t\t%d\t\t%d\n", currentId, newTest1, newTest2 );
				break;
			}
		}
		*/

		fclose( cfPtr );
	}
}