//----------------------------------
// File:		fileaccessusingtextbook.cpp
// Created:		2012/04/22
// Copyright:	Daniel Schenker
//----------------------------------

//fopen		: Opens a file.
	///FILE * fopen ( const char * filename, const char * mode );
		/*
		r	Open an existing file for reading. If the file doesn't exist it will set the pointer to NULL.
		w	Create a file for writing. If the file already exists, discard the current contents.
		a	Append; open or create a file for writing at the end of the file.
		r+	Open an existing file for update (reading and writing).
		w+	Create a file for update. If the file already exists, discard the current contents.
		a+	Apeend: open or create a file for update; writing is done at the end of the file.
		rb	Open an existing file for reading in binary mode.
		wb	Create a file for writing in binary mode. If the file already exists, discard the current contents.
		ab	Append; open or create a file for writing at the end of the file in binary mode.
		wb+	Create a file for update in binary mode. If the file already exists, discard the current contents.
		ab+	Append: open or create a file for update in binary mode; writing is done at the end of the file.
		*/

//fclose	: Closes a file.
	///int fclose ( FILE * stream );
	//always close files after opening them

//fseek		: Seeks to a specific position in a file (starts counting with 0).
	///int fseek ( FILE * stream, long int offset, int origin );
		/*
		stream
			Pointer to a FILE object that identifies the stream. 
		offset
			Number of bytes to offset from origin.
		origin
			Position from where offset is added. It is specified by one of the following constants defined in <cstdio>:
				SEEK_SET	Seeks forward from the eginning of file
				SEEK_CUR	Seeks forward from the current position of the file pointer
				SEEK_END	Seeks backward from the end of file
		*/

//fwrite	: Writes an array of count elements, each one with a size of size bytes, from the block of memory pointed by ptr to the current position in the stream.
			//The postion indicator of the stream is advanced by the total number of bytes written.
			//The total amount of bytes written is (size * count).
	///size_t fwrite ( const void * ptr, size_t size, size_t count, FILE * stream );

//fread		: Same as fwrite, but reads instead of writes.
	///size_t fread ( void * ptr, size_t size, size_t count, FILE * stream );

//feof		: Returns true when at the end of a file.
	///int feof ( FILE * stream );
			/*
				End-of-filekey combinations for various popular operating systems:
					Linux/MacOSX/UNIX		<Ctrl> d
					Windows					<Ctrl> z
			*/

//fprintf	: Writes to the data formatted as the format argument specifies.
	///int fprintf ( FILE * stream, const char * format, ... );

//fscanf	: Reads data and stores them.
	///int fscanf ( FILE * stream, const char * format, ... );

//fgetc		: Returns the character currently pointed by the internal file position indicator of the specified stream.
			//The internal file position indicator is then advanced by one character to point to the next character.
				//Note: fgetc and getc are equivalent, except that the latter one may be implemented as a macro.
	///int fgetc ( FILE * stream );

//fputc		: Writes a character to the stream and advances the position indicator.
	///int fputc ( int character, FILE * stream );

//Creating a random-access file sequentially

#include <stdio.h>

struct clientData
{
	int acctNum;			//account number
	char lastName[ 15 ];	//account last name
	char firstName[ 10 ];	//account first name
	double balance;			//account balance
};

int main()
{
	int i;

	//create clientData with default information
	struct clientData blankClient = { 0, "", "", 0.0 };

	FILE *cfPtr;
	
	//Open a file to write in binary
	if( ( cfPtr = fopen( "credit.dat", "wb" ) ) == NULL)//Can not open file
	{
		printf( "File could not be opened.\n" );
	}
	else//File opened succesfully
	{
		//output 100 blank records to file
		for(i = 1; i <= 100; ++i)
		{
			fwrite(&blankClient, sizeof( struct clientData ), 1, cfPtr);
		}
		fclose(cfPtr);
	}//end else

	return 0;
}