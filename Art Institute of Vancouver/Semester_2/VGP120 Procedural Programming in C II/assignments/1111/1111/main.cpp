#include <stdio.h>

struct person{
	char lastName[15];
	char firstName[15];
	char age[4];
};

// function prototypes
void organizeFile(FILE *, person);

int main()
{
	int counter = 0;

	FILE *cfPtr = fopen( "nameage.dat", "wb+" );
	if ( ( cfPtr = fopen( "nameage.dat", "wb+" ) ) == NULL )
	{
		printf( "File could not be opened.\n" );
	}

	struct person master = { "unassigned", "", 0 };

	organizeFile(cfPtr, master);

	for (int i = 0; i < 10; ++i )
	{ 
		printf( "Enter lastname, firstname, age\n? " );

		fscanf( stdin, "%s%s%lf", master.lastName, master.firstName, &master.age );

		fseek( cfPtr, ( i ) * 
			sizeof( struct mFile ), SEEK_SET );

		fwrite( &master, sizeof( struct person ), 1, cfPtr );
	}

	//update
	printf( "Which entry would you like to edit ( 1 to 100, 0 to end input )\n? " );
	scanf( "%d", &counter );

	while ( counter != 0 )
	{ 

		printf( "Enter lastname, firstname, age\n? " );

		fscanf( stdin, "%s%s%lf", master.lastName, master.firstName, &master.age );

		fseek( cfPtr, ( counter - 1 ) * 
			sizeof( struct person ), SEEK_SET );

		if ( (fread( &master, (struct person ), 1, cfPtr) ==  { "unassigned", "", 0 })
		{
			printf("No info\n");
		}

		fwrite( &master, sizeof( struct person ), 1, cfPtr );

		printf( "Enter entry number\n? " );
		scanf( "%d", &counter );
	}

	//reinitialize
	printf( "Which entry would you like to reinitialize ( 1 to 100, 0 to end input )\n? " );
	scanf( "%d", &counter );

	master = { "unassigned", "", 0 };

	while ( counter != 0 )
	{ 
		fseek( cfPtr, ( counter - 1 ) * 
			sizeof( struct person ), SEEK_SET );

		fwrite( &master, sizeof( struct person ), 1, cfPtr );

		printf( "Enter entry number\n? " );
		scanf( "%d", &counter );
	}

	fclose( cfPtr );

	return 0;
}

void organizeFile(FILE *fPtr, person master)
{
	for ( int i = 0; i < 100; ++i )
	{
		fwrite( &master, sizeof( struct person ), 1, fPtr );
	}

}//end of organizeFile()