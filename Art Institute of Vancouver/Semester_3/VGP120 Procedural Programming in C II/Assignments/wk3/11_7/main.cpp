//---------------------------------------------------------------
// File name: main.cpp
// Created On: 01/24/2012
// Copyright: Daniel Schenker
//---------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//function prototypes
//---------------------------------------------------------------
void GenerateStudentInfo( struct student*, const unsigned int );
void SequentialWrite( struct student*, const unsigned int, char* );
void UpdateInfo( const unsigned int );
//---------------------------------------------------------------


//globals
//---------------------------------------------------------------
struct student
{
	unsigned int id;
	unsigned char name[3];
	float money;
};
//---------------------------------------------------------------


int main()
{
	const unsigned int kAmountOfStudents = 50;
	struct student oldmast[kAmountOfStudents];
	struct student* oldmastPtr = &oldmast[0];
	struct student trans[kAmountOfStudents];
	struct student* transPtr = &trans[0];
	struct student newmast[kAmountOfStudents];
	struct student* newmastPtr = &newmast[0];
	char* fileName = ( char* )malloc( 15 );

	int choice = 0;

	srand( (unsigned)time(NULL) );

	fileName = "oldmast.dat";
	SequentialWrite( oldmastPtr, kAmountOfStudents, fileName );
	fileName = "trans.dat";
	SequentialWrite( transPtr, kAmountOfStudents, fileName );
	fileName = "newmast.dat";
	SequentialWrite( newmastPtr, kAmountOfStudents, fileName );
	
	UpdateInfo( kAmountOfStudents );

	return 0;
}




void GenerateStudentInfo( struct student* listPtr, const unsigned int kAmountOfStudents )
{
	for( int i = 0; i < kAmountOfStudents; ++i )
	{
		listPtr[i].id = i;
		for( int j = 0; j < 3; ++j )
		{
			listPtr[i].name[j] = (char)(rand() % 25 + 65);
		}
		listPtr[i].money = rand() % 2001;
	}
}




void SequentialWrite( struct student* listPtr, const unsigned int kAmountOfStudents, char* fileName )
{
	FILE *cfPtr;//cfPtr = marks.dat file pointer

	//fopen opens file. Exit program if unable to create file
	if( (cfPtr = fopen(fileName, "w")) == NULL )
	{
		printf( "AAAAAFile could not be opened\n" );
	}
	else
	{
		GenerateStudentInfo( listPtr, kAmountOfStudents );

		for( int i = 0; i < kAmountOfStudents; ++i )
		{
			fprintf( cfPtr, "%d\t\t",  listPtr[i].id );
			for( int j = 0; j < 3; ++j )
			{
				fprintf(cfPtr, "%c", listPtr[i].name[j] );
			}
			fprintf( cfPtr, "\t\t%.2f\n", listPtr[i].money );
		}	
		fclose( cfPtr );
	}
}




void UpdateInfo( const unsigned int kAmountOfStudents )
{
	unsigned int oId;
	unsigned char oName[3];
	float oMoney;
	
	unsigned int tId;
	unsigned char tName[3];
	float tMoney;
	
	float nMoney = 0;

	unsigned int counter = 0;

	for( int i = 0; i < kAmountOfStudents; ++i )
	{
		FILE *ofPtr;
		if( (ofPtr = fopen("oldmast.dat", "r")) == NULL )
		{
			printf( "oldmast.dat file could not be opened\n" );
		}
		else
		{	
			fseek( ofPtr, counter * (sizeof (struct student)), SEEK_SET );
			fscanf( ofPtr, "%d",  &oId );
			for( int j = 0; j < 3; ++j )
			{
				fscanf(ofPtr, "%c", &oName[j] );
			}
			fscanf( ofPtr, "%f", &oMoney );
	
			fclose( ofPtr );
		}

		FILE *tfPtr;
		if( (tfPtr = fopen("trans.dat", "r")) == NULL )
		{
			printf( "trans.dat file could not be opened\n" );
		}
		else
		{	
			fseek( tfPtr, counter * (sizeof (struct student)), SEEK_SET );
			fscanf( tfPtr, "%d",  &tId );
			for( int j = 0; j < 3; ++j )
			{
				fscanf(tfPtr, "%c", &tName[j] );
			}
			fscanf( tfPtr, "%f", &tMoney );
		}
		fclose( tfPtr );

		nMoney = oMoney + tMoney;

		printf("%d",nMoney);

		fflush(stdin);

		FILE *nfPtr;
		if( (nfPtr = fopen("newmast.dat", "w")) == NULL )
		{
			printf( "newmast.dat file could not be opened\n" );
		}
		else
		{	
			//fseek( nfPtr, counter * (sizeof (struct student)), SEEK_SET );
			fprintf( nfPtr, "%d\t\t",  oId );
			for( int j = 0; j < 3; ++j )
			{
				fprintf(nfPtr, "%c", oName[j] );
			}
			fprintf( nfPtr, "\t\t%.2f\n", nMoney );
		}
		fclose( nfPtr );

		++counter;
	}

}