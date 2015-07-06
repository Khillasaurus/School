//----------------------------------
// File:		fileaccess.cpp
// Created:		2012/04/18
// Copyright:	Daniel Schenker
//----------------------------------
	//Note: All file related functions are referenced at the bottom of this cpp file

#include <stdio.h>
#include <cstdlib>
#include <conio.h>

const int kNameBuffSize = 20;

struct clientData
{
	int acctNum;
	char lastName[kNameBuffSize];
	char firstName[kNameBuffSize];
	float balance;
};

//------------FUNCTION PROTOTYPES-------------
//Menu Related
int MainMenu();
//Program Specific
char* ClearFile(FILE*&, bool&, char*);
void EditSingleRecord(FILE*&, char*);
void ReadSingleRecord(FILE*&, char*);
void DeleteSingleRecord(FILE*&, char*);
//File Related
void SeekByCharacterNumber();
void SequentialWriteNoSeek();
void RandomAccessWriteWithoutSeek();
void RandomAccessWriteWithSeek();
void PrintFile(FILE*&, char*);
long int GetFileSize(FILE*&, char*);
//Unit Tests
void UnitTestAll();
//Utitity
bool UserAgrees();
int EnsurePositive(int);
void EnsureWithinBoundaries(int&, const int, const int);

int main()
{
	bool fileExists = false;
	FILE* fp;
	char* pFileName = "0";
	int choice = MainMenu();

	//While the user doesn't want to quit
	while(choice != 5)
	{
		switch(choice)
		{
			case 1: //Rewrite (or create) a new database
				pFileName = ClearFile(fp, fileExists, pFileName);
				break;
			case 2: //User can change a single record of their choice
				if(fileExists)
				{
					EditSingleRecord(fp, pFileName);
				}
				break;
			case 3: //Display a single record of the user's choice
				if(fileExists)
				{
					ReadSingleRecord(fp, pFileName);
				}
				break;
			case 4: //User can reset a single record of their choice
				if(fileExists)
				{
					DeleteSingleRecord(fp, pFileName);
				}
				break;
			case 5://Quit the program
				break;
			default:
				printf("ERROR: Invalid given. The variable \"option\" must be between 1 and 5. Quiting program.\n");
				break;
		}
		if((choice != 1) && (!fileExists))//Check to see if a database exists
		{
			printf("No database exists. One must be created first from Option 1 \"Wipe whole blank file\"\n");
		}
		 //Note: This caused an error on my computer at home, and due to being unable to resolve it after many hours of research I'm going to comment it out. If I forget to comment it back in when I hand it in, that's why.
		//printf("\nEnter any key to return to the main menu.");
		//while(!_kbhit())//While no key has been entered. I use _khbit() or khbit as kkhbit is prior to 2005, and as a result does not include the escape key when called.
		//{
		//}
		fflush(fp);//Explained in reference at bottom of cpp
		//system("pause");//Another method I was testing that also caused issues.
		//std::system("CLS");

		choice = MainMenu();
	}

	printf("Thank you for using Daniel Schenker's Client Manager Service.\n");
	printf("Goodbye.\n");


	return 0;
}

int MainMenu()
{
	int choice = -1;

	printf("Enter your choice:\n");
	printf("1 - Wipe whole blank file\n");
	printf("2 - Change a Customer\n");
	printf("3 - Read a Customer\n");
	printf("4 - Delete a Customer\n");
	printf("5 - Quit\n");
	scanf("%d", &choice);
	EnsureWithinBoundaries(choice, 1, 5);
	printf("\n");

	return choice;
}

char* ClearFile(FILE*& fp, bool& fileExists, char* pFileName)
{
	const int kRecords = 100;
	clientData database[kRecords] = {0, "", "",0.0};
	clientData* pDatabase = &database[0];
	char fileName[] = "customers.dat";
	pFileName = &fileName[0];

	for(int i = 0; i < kRecords; ++i)
	{
		database[i].acctNum = i;
	}
	
	if(!(fp = fopen(pFileName, "wb")))
	{
		printf("ERROR: Can't open file!\n");
	}
	else
	{
		fileExists = true;
		if((fwrite(pDatabase, sizeof(clientData), kRecords, fp)) != kRecords)
		{
			printf("ERROR: Could not finish writing data to %s in the ClearFile() function.\n", *pFileName);
		}
		fflush(fp);
		fclose(fp);
	}

	printf("The file is now blank.\n");

	return pFileName;
}

void EditSingleRecord(FILE*& fp, char* pFileName)
{
	clientData database = {0, "", "", 0.0};

	printf("Which customer file would you like to edit?\n");
	scanf("%d", &(database.acctNum));
	EnsureWithinBoundaries(database.acctNum, 1, 100);

	if(!(fp = fopen(pFileName, "rb+")))
	{
		printf("ERROR: Can't open file!\n");
	}
	else
	{
		fseek(fp, database.acctNum - 1, SEEK_SET);
		printf("Enter the new information for this account:\n");
		printf("Last Name: ");
		scanf("%s", &(database.lastName));
		printf("First Name: ");
		scanf("%s", &(database.firstName));
		printf("Balance: ");
		scanf("%f", &(database.balance));
		if((fwrite(&database, sizeof(clientData), 1, fp)) != 1)
		{
			printf("ERROR: Could not finish writing data to %s in the EditSingleRecord() function.\n", *pFileName);
		}

		fflush(fp);

		fclose(fp);
	}
}

void ReadSingleRecord(FILE*& fp, char* pFileName)
{
	int accountNum = -1;
	clientData database = {0, "", "", 0.0};

	printf("Which customer file would you like to read?\n");
	scanf("%d", &accountNum);
	EnsureWithinBoundaries(accountNum, 1, 100);

	if(!(fp = fopen(pFileName, "rb")))
	{
		printf("ERROR: Can't open file!\n");
	}
	else
	{
		fseek(fp, accountNum-1, SEEK_SET);
		if((fread(&database, sizeof(clientData), 1, fp)) != 1)
		{
			printf("ERROR: Could not finish reading data from %s in the ReadSingleRecord() function.\n", *pFileName);
		}
		if(ferror(fp))
		{
			printf("%s\n", ferror(fp));
		}
		if(database.acctNum == 0)
		{
			printf("ERROR - This customer does not exist\n");
		}
		else
		{
			printf("%-6s%-21s%-21s%10s\n", "Acct", "Last Name", "First Name", "Balance");
			printf("%-6d%-21s%-21s%10.2f\n", database.acctNum, database.lastName, database.firstName, database.balance);
		}
		fclose(fp);
	}
}

void DeleteSingleRecord(FILE*& fp, char* pFileName)
{
	clientData database = {0, "", "", 0.0};

	printf("Which customer file would you like to delete?\n");
	scanf("%d", &(database.acctNum));
	EnsureWithinBoundaries(database.acctNum, 1, 100);

	if(!(fp = fopen(pFileName, "rb+")))
	{
		printf("ERROR: Can't open file!\n");
	}
	else
	{
		fseek(fp, database.acctNum - 1, SEEK_SET);
		database.acctNum = 0;
		if((fwrite(&database, sizeof(clientData), 1, fp)) != 1)
		{
			printf("ERROR: Could not finish writing data to %s in the DeleteSingleRecord() function.\n", *pFileName);
		}
		fflush(fp);

		fclose(fp);
	}
}

void SeekByCharacterNumber()
{
	FILE* myFile;
	const char kFileName[] = "SeekByCharacterNumber.txt";

	if(!(myFile = fopen(kFileName, "w")))
	{
		printf("ERROR: Can't open file!\n");
	}
	else
	{
		fputs("This is an apple.", myFile);
		fseek(myFile , 9 , SEEK_SET);
		fputs(" sam" , myFile);
		fclose(myFile);
	}
}

void SequentialWriteNoSeek()
{
	int account = 1;
	char name[31];
	float balance;
	const char kFileName[] = "SequentialWriteNoSeek.txt";

	FILE* myFile = fopen(kFileName, "w");
	
	if(!myFile)//myFile == NULL
	{
		printf("ERROR: Could not open file for writing\n");
	}
	else
	{
		fprintf(myFile, "Account #\tName\t\tBalance\n");
		while(1)
		{
			printf("Would you like to add to the file?\n");
			printf("Enter 1 for yes, 0 for no.\n");
			if(UserAgrees())
			{
				printf("Enter name (max 30 characters):\n");
				scanf("%s", &name);
				printf("How much money is in the balance?\n");
				scanf("%f", &balance);
				fprintf(myFile, "%d\t\t%s\t\t%.2f\n", account, name, balance);
				++account;
			}
			else
			{
				break;
			}
		}
	}
	fclose(myFile);
}

void RandomAccessWriteWithoutSeek()
{
	clientData bankClient;
	const char kFileName[] = "RandomAccessWriteWithoutSeek.dat";

	FILE* fp = fopen(kFileName, "wb");
	if(!fp)
	{
		printf("ERROR: Can't open file!\n");
	}
	else
	{
		if((fwrite(&bankClient, sizeof(clientData), 100, fp)) != 100)
		{
			printf("ERROR: Could not finish writing data to %s in the RandomAccessWriteWithoutSeek() function.\n", kFileName);
		}
		fflush(fp);
	}

	fclose(fp);
}

void RandomAccessWriteWithSeek()
{
	const char kFileName[] = "RandomAccessWriteWithSeek.dat";
	int recordCount = 0;
	clientData blank;
	clientData bankClient;
	bankClient.acctNum = -1;

	printf("Would you like to create a new bank file? (1 for yes, 0 for no)\n");
	if(UserAgrees())
	{
		FILE* fp = fopen(kFileName, "wb");
	
		if(!fp)//Can not open file
		{
			printf("ERROR: Can't open file!\n");
		}
		else//File opened succesfully
		{
			printf("A blank bank file has been created.\n");
			while(bankClient.acctNum != 0)
			{
				printf("Enter the account number that you would like to edit. (1 - 100), 0 to end)\n");
				scanf("%d", &(bankClient.acctNum));
				EnsureWithinBoundaries(bankClient.acctNum, 0, 100);
				
				if(bankClient.acctNum != 0)
				{
					//Check if new blank placeholder accounts need to be created or not
					if(recordCount < (bankClient.acctNum - 1))
					{
						//Set total account count to biggest account number
						recordCount = bankClient.acctNum;

						//Go to end of file
						fseek(fp, sizeof(blank), SEEK_END);

						//Create new blank placeholder accounts
						if((fwrite(&blank, sizeof(blank), (bankClient.acctNum - recordCount), fp)) != (bankClient.acctNum - recordCount))
						{
							printf("ERROR: Could not finish writing data to %s in the RandomAccessWriteWithSeek() function.\n", kFileName);
						}
						fflush(fp);
					}

					//Create or replace an account with new information
					printf("Enter last name, first name and balance.\n");
					scanf("%s", &(bankClient.lastName));
					scanf("%s", &(bankClient.firstName));
					scanf("%f", &(bankClient.balance));
					fseek(fp, ((bankClient.acctNum - 1) * sizeof(clientData)), SEEK_SET);
					if((fwrite(&bankClient, sizeof(clientData), 1, fp)) != 1)
					{
						printf("ERROR: Could not finish writing data to %s in the RandomAccessWriteWithSeek() function.\n", kFileName);
					}
					fflush(fp);
					fflush(fp);
				}
				else
				{
					break;
				}
			}
		}
	fclose(fp);
	}
}

void PrintFile(FILE*& fp, char* pFileName)
{
	fseek(fp, 0, SEEK_SET);

	clientData database = {0, "", "", 0.0};

	if(!(fp = fopen(pFileName, "rb")))
	{
		printf("ERROR: Can't open file!\n");
	}
	else
	{
		printf("%-6s%-21s%-21s%10s\n", "Acct", "Last Name", "First Name", "Balance");
		while(!feof(fp))
		{
			if((fread(&database, sizeof(clientData), 1, fp)) != 1)
			{
				printf("ERROR: Could not finish reading data from %s in the PrintFile() function.\n", *pFileName);
			}
			printf("%-6d%-21s%-21s%10.2f\n", database.acctNum, database.lastName, database.firstName, database.balance);
		}
		if(ferror(fp))
		{
			printf("%s\n", ferror(fp));
		}
		fclose(fp);
	}
}

long int GetFileSize(FILE*& fp, char* pFileName)
{
	long fileSize = -1;

	if(!(fp = fopen(pFileName, "rb")))
	{
		printf("ERROR: Can't open file!\n");
	}
	else
	{
		fseek(fp, 0, SEEK_END);
		fileSize = ftell(fp);
	}

	return fileSize;
}

void UnitTestAll()
{
	printf("Running SeekByCharacterNumber()...\n");
	SeekByCharacterNumber();
	printf("SeekByCharacterNumber() Finished.\n\n");

	printf("Running SequentialWriteNoSeek()...\n");
	SequentialWriteNoSeek();
	printf("SequentialWriteNoSeek() Finished.\n\n");

	printf("Running RandomAccessWriteWithoutSeek()...\n");
	RandomAccessWriteWithoutSeek();
	printf("RandomAccessWriteWithoutSeek() Finished.\n\n");

	printf("Running RandomAccessWriteWithSeek()...\n");
	RandomAccessWriteWithSeek();
	printf("RandomAccessWriteWithSeek() Finished.\n\n");

	printf("All done!\n");
}

bool UserAgrees()
{
	int choice = -1;
	while(choice < 0 || choice > 1)
	{
		scanf("%d", &choice);
		if(choice < 0 || choice > 1)
		{
			printf("Invalid option. Please choose again.\n");
		}
	}

	if(choice == 1)
	{
		return true;
	}
	else
	{
		return false;
	}
}

int EnsurePositive(int choice)
{
	while(choice < 0)
	{
		printf("Invalid option. You must enter a positive value.\n");
		printf("Please choose again.\n");
		scanf("%d", choice);
	}
	return choice;
}

void EnsureWithinBoundaries(int& answer, const int lower, const int upper)
{
	while(answer < lower || answer > upper)
	{
		if(answer < lower)
		{
			printf("Invalid answer. You must enter a value greater than %d.\n", (lower - 1));
			scanf("%d", &answer);
		}
		else if(answer > upper)
		{
			printf("Invalid answer. You must enter a value less than %d.\n", (upper + 1));
			scanf("%d", &answer);
		}
	}
}


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

//fwrite	: Writes an array of count elements, each one with a size of size bytes, from the block of memory pointed by ptr to the current position in the stream.
	///size_t fwrite ( const void * ptr, size_t size, size_t count, FILE * stream );
		//The postion indicator of the stream is advanced by the total number of bytes written.
		//The total amount of bytes written is (size * count).
			/* Return:
			The total number of elements successfully written is returned as a size_t object, which is an integral data type.
			If this number differs from the count parameter, it indicates an error.
			*/

//fread		: Same as fwrite, but reads instead of writes.
	///size_t fread ( void * ptr, size_t size, size_t count, FILE * stream );
			/* Return:
			The total number of elements successfully read is returned as a size_t object, which is an integral data type.
			If this number differs from the count parameter, either an error occured or the End Of File was reached.
			You can use either ferror or feof to check whether an error happened or the End-of-File was reached.
			*/

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

//feof		: Returns true when at the end of a file.
	///int feof ( FILE * stream );
			/*
				End-of-filekey combinations for various popular operating systems:
					Linux/MacOSX/UNIX		<Ctrl> d
					Windows					<Ctrl> z
			*/

//fprintf	: Writes to the data formatted as the format argument specifies.
	///int fprintf ( FILE * stream, const char * format, ... );
			/* Return:
			On success, the total number of characters written is returned.
			On failure, a negative number is returned.
			*/

//fscanf	: Read formatted data from stream
	///int fscanf ( FILE * stream, const char * format, ... );
			/* Return:
			On success, the function returns the number of items successfully read. This count can match the expected number of readings or be less -even zero- in the case of a matching failure.
			In the case of an input failure before any data could be successfully read, EOF is returned.
			*/

//fputs		: Write string to stream
	///int fputs ( const char * str, FILE * stream );
		//Note: The final null-character is not copied to the stream.
			/* Return:
			On success, a non-negative value is returned.
			On error, the function returns EOF.
			*/

//fgets		: Get string from stream
	///char * fgets ( char * str, int num, FILE * stream );
		/*
		Reads characters from stream and stores them as a C string into str until (num-1) characters have been read or either a newline or the End-of-File is reached, whichever comes first.
		A newline character makes fgets stop reading, but it is considered a valid character and therefore it is included in the string copied to str.
		A null character is automatically appended in str after the characters read to signal the end of the C string.
		*/
			/* Return:
			On success, the function returns the same str parameter.
			If the End-of-File is encountered and no characters have been read, the contents of str remain unchanged and a null pointer is returned.
			If an error occurs, a null pointer is returned.
			Use either ferror or feof to check whether an error happened or the End-of-File was reached.
			*/

//fgetc		: Get character from stream
	///int fgetc ( FILE * stream );
		//The internal file position indicator is then advanced by one character to point to the next character.
		 //Note: fgetc and getc are equivalent, except that the latter one may be implemented as a macro.
			//Return: the character currently pointed by the internal file position indicator of the specified stream.

//fputc		: Write character to stream
	///int fputc ( int character, FILE * stream );
		//Writes a character to the stream and advances the position indicator.

//fflush	: Explicit call to flush a stream (as opposed to flushing with: fseek, fsetpos or rewind.
	///int fflush ( FILE * stream );
		/*
		-If the given stream was open for writing and the last i/o operation was an output operation, any unwritten data in the output buffer is written to the file.
		-If it was open for reading and the last operation was an input operation, the behavior depends on the specific library implementation. In some implementations this causes the input buffer to be cleared, but this is not standard behavior.
		-If the argument is a null pointer, all open files are flushed.
		-The stream remains open after this call.
		-When a file is closed, either because of a call to fclose or because the program terminates, all the buffers associated with it are automatically flushed.
		*/
			/* Return:
			A zero value indicates success.
			If an error occurs, EOF is returned and the error indicator is set (see feof).
			*/
