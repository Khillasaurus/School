#include <stdio.h>

struct mFile
{ 
	int recordNumber;
	char toolName[10];
	int quantity;
	double cost;
	char newLine;
};

// function prototypes
void organizeFile(FILE *, mFile);

int main()
{

	FILE *cfPtr = fopen( "hardware.dat", "wb+" );
	if ( ( cfPtr = fopen("hardware.dat", "wb+" ) ) == NULL )
	{
		printf( "File could not be opened.\n" );
	}

	struct mFile master = { 0, "", 0, 0.0, '\n' };

	organizeFile(cfPtr, master);

	printf( "Enter account number ( 1 to 100, 0 to end input )\n? " );
	scanf( "%d", &master.recordNumber );

	while ( master.recordNumber != 0 )
	{ 

		printf( "Enter toolName, quantity, cost\n? " );

		fscanf( stdin, "%s%d%lf", master.toolName, master.quantity, &master.cost );

		fseek( cfPtr, ( master.recordNumber - 1 ) * 
			sizeof( struct mFile ), SEEK_SET );

		fwrite( &master, sizeof( struct mFile ), 1, cfPtr );

		printf( "Enter account number\n? " );
		scanf( "%d", &master.recordNumber );
	}

	fclose( cfPtr );

	return 0;
}

void organizeFile(FILE *fPtr, mFile master)
{
	int counter = 0;
	for ( int i = 0; i < 100; ++i )
	{
		fwrite( &master, sizeof( struct mFile ), 1, fPtr );
	}

	fseek( cfPtr, ( counter ) * sizeof( struct mFile ), SEEK_SET );
	master = { 3, "Electric Sander", 7, 57.98, '\n' };
	fwrite( &master, sizeof( struct mFile ), 1, fPtr );

	fseek( cfPtr, ( counter ) * sizeof( struct mFile ), SEEK_SET );
	master = { 17, "Hammer", 76, 11.99, '\n' };
	fwrite( &master, sizeof( struct mFile ), 1, fPtr );

	fseek( cfPtr, ( counter ) * sizeof( struct mFile ), SEEK_SET );
	master = { 24, "Jig Saw", 21, 11.00, '\n' };
	fwrite( &master, sizeof( struct mFile ), 1, fPtr );

	fseek( cfPtr, ( counter ) * sizeof( struct mFile ), SEEK_SET );
	master = { 39, "Lawn Mover", 3, 79.50, '\n' };
	fwrite( &master, sizeof( struct mFile ), 1, fPtr );

	fseek( cfPtr, ( counter ) * sizeof( struct mFile ), SEEK_SET );
	master = { 56, "Power Saw", 18, 99.99, '\n' };
	fwrite( &master, sizeof( struct mFile ), 1, fPtr );

	fseek( cfPtr, ( counter ) * sizeof( struct mFile ), SEEK_SET );
	master = { 68, "Screwdriver", 106, 6.99, '\n' };
	fwrite( &master, sizeof( struct mFile ), 1, fPtr );

	fseek( cfPtr, ( counter ) * sizeof( struct mFile ), SEEK_SET );
	master = { 77, "Sledgehammer", 11, 21.50, '\n' };
	fwrite( &master, sizeof( struct mFile ), 1, fPtr );

	fseek( cfPtr, ( counter ) * sizeof( struct mFile ), SEEK_SET );
	master = { 83, "Wrench", 34, 7.50, '\n' };
	fwrite( &master, sizeof( struct mFile ), 1, fPtr );

}//end of organizeFile()