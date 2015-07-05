#include <stdio.h>

/* information structure definition */
struct information
{ 
	int studentNumber;
	char lastName[15];
	char firstName[10];
	double balance;
	char newLine;
}; /* end structure information */

void createFile(FILE *, information);

int main()
{
	FILE *cfPtr=fopen( "data.txt", "wb+" );
	/* fopen opens the file; exits if file cannot be opened */
	if ( ( cfPtr = fopen( "data.txt", "wb+" ) ) == NULL )
	{
		printf( "File could not be opened.\n" );
	} /* end if */

	/* create clientData with default information */
	struct information info = { 0, "", "", 0.0, '\n' };

	createFile(cfPtr, info);

	/* require user to specify account number */
	printf( "Enter student number ( 1 to 100, 0 to end input )\n? " );
	scanf( "%d", &info.studentNumber );

	/* user enters information, which is copied into file */
	while ( info.studentNumber != 0 )
	{ 

		/* user enters last name, first name and balance */
		printf( "Enter lastname, firstname, balance\n? " );

		/* set record lastName, firstName and balance value */
		fscanf( stdin, "%s%s%lf", info.lastName, 
			info.firstName, &info.balance );

		/* seek position in file to user-specified record */
		fseek( cfPtr, ( info.studentNumber - 1 ) * 
			sizeof( struct information ), SEEK_SET );

		/* write user-specified information in file */
		fwrite( &info, sizeof( struct information ), 1, cfPtr );

		/* enable user to input another account number */
		printf( "Enter account number\n? " );
		scanf( "%d", &info.studentNumber );
	} /* end while */

	fclose( cfPtr ); /* fclose closes the file */

	return 0;
}

void createFile(FILE *fPtr, information info)
{
	for ( int i = 0; i < 100; ++i )
	{
		fwrite( &info, sizeof( struct information ), 1, fPtr );
	}

}//end of createFile()
