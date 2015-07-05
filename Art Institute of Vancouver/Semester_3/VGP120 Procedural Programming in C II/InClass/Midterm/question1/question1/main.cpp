#include <stdio.h>

int main()
{
	int lineCount = 0;
	int mainLineNumber = 0;
	int gCount = 0;		// >
	int lCount = 0;		// <
	int gOECount = 0;	// >=
	int lOECount = 0;	// <=
	int eTCount = 0;	// ==
	int nETCount = 0;	// !=
	bool foundMain = false;
	char character[6];
	bool insideQuote = false;


	FILE *cfPtr;

	if((cfPtr = fopen("test.cpp", "r")) == NULL)
	{
		printf("File could not be opened\n");
	}
	else
	{
		while(!feof(cfPtr))
		{
			fscanf(cfPtr, "%c", &character[0]);
			if(character[0] == '\n')
			{
				++lineCount;
			}

			if(!foundMain)
			{
				if(character[0] == 'm')
				{
					for(int i = 0; i < 5; ++i)
					{
						fscanf(cfPtr, "%c", &character[i+1]);
					}
					if((character[0] == 'm') && (character[1] == 'a') && (character[2] == 'i') && (character[3] == 'n') && (character[4] == '(') && (character[5] == ')'))
					{
						foundMain = true;
						mainLineNumber = lineCount;
					}
				}
			}
			if(character[0] == '\"')
			{
				insideQuote == !insideQuote;
			}
			if(!insideQuote)
			{
				if(character[0] == '>')
				{
					fscanf(cfPtr, "%c", &character[0]);
					if(character[0] == '=')
					{
						++gOECount;
					}
					else
					{
					++gCount;
					}
				}
				if(character[0] == '<')
				{
					fscanf(cfPtr, "%c", &character[0]);
					if(character[0] == '=')
					{
						++lOECount;
					}
					else
					{
					++lCount;
					}
				}
				if(character[0] == '=')
				{
					fscanf(cfPtr, "%c", &character[0]);
					if(character[0] == '=')
					{
						++eTCount;
					}
				}
				if(character[0] == '!')
				{
					fscanf(cfPtr, "%c", &character[0]);
					if(character[0] == '=')
					{
						++nETCount;
					}
				}
			}
		}
		fclose(cfPtr);
	}

	printf("Main function is on line #%d\n", mainLineNumber);
	printf("The count of relational operators are as follows,\n");
	printf(">  :%d\n", gCount);
	printf("<  :%d\n", lCount);
	printf(">= :%d\n", gOECount);
	printf("<= :%d\n", lOECount);
	printf("== :%d\n", eTCount);
	printf("!= :%d\n", nETCount);

	return 0;
}