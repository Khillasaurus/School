#include <stdio.h>

struct mFile
{ 
	int accountNumber;
	char firstName[10];
	char lastName[15];
	double balance;
	char newLine;
};

// function prototypes
void organizeFile(FILE *, mFile);

int main()
{

	FILE *cfPtr = fopen( "mast.dat", "wb+" );
	if ( ( cfPtr = fopen("mast.dat", "wb+" ) ) == NULL )
	{
		printf( "File could not be opened.\n" );
	}

	struct mFile master = { 0, "", "", 0.0, '\n' };

	organizeFile(cfPtr, master);

	printf( "Enter account number ( 1 to 100, 0 to end input )\n? " );
	scanf( "%d", &master.accountNumber );

	while ( master.accountNumber != 0 )
	{ 

		printf( "Enter firstname, lastname, balance\n? " );

		fscanf( stdin, "%s%s%lf", master.firstName, master.lastName, &master.balance );

		fseek( cfPtr, ( master.accountNumber - 1 ) * 
			sizeof( struct mFile ), SEEK_SET );

		fwrite( &master, sizeof( struct mFile ), 1, cfPtr );

		printf( "Enter account number\n? " );
		scanf( "%d", &master.accountNumber );
	}

	fclose( cfPtr );

	return 0;
}

void organizeFile(FILE *fPtr, mFile master)
{
	for ( int i = 0; i < 100; ++i )
	{
		fwrite( &master, sizeof( struct mFile ), 1, fPtr );
	}

}//end of organizeFile()



//Question 11.1
/*
struct person
{
char lastName[15];
char firstName[15];
char age[4];
};

a)
	FILE *cfPtr = fopen( "nameage.dat", "wb+" );
	if ( ( cfPtr = fopen("nameage.dat", "wb+" ) ) == NULL )
	{
		printf( "File could not be opened.\n" );
	}
	else
	{
		struct person abc = { "unasigned", "", "0" };
		for ( int i = 0; i < 100; ++i )
		{
			fwrite( &abc, sizeof( struct person ), 1, fPtr );
		}
	}

b)

	printf( "Enter last name, name and age.\n" );
	scanf( "%c%c%c", &abc.lastName, &abc.firstName, &abc.age );
	
	for ( int j = 0; j < 10; ++j )
	{
		printf( "Enter lastname, firstname, age\n? " );

		fscanf( stdin, "%s%s%c", &abc.lastName, abc.&firstName, &abc.age );

		fseek( cfPtr, ( abc.j - 1 ) * sizeof( struct person ), SEEK_SET );
c)
d)
		fwrite( &abc, sizeof( struct person ), 1, cfPtr );

		printf( "Enter last name, name and age.\n" );
		scanf( "%c%c%c", &abc.lastName, &abc.firstName, &abc.age );
	}