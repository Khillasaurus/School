#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

void concatenate(char *article, char *noun, char *verb, char *preposition, char *holdPtr)
{

    int word = -1;
    char sentence[100] = {'0'};

    word = rand()%4;
    for(int i = 0; i < word; i++)
    {
        while(holdPtr!=" ")
        {
            holdPtr++;//infinite loop = BAD!
        }
    }
    strcpy (sentence,(holdPtr+4));

    for(int i = 0; i < 20; i++)
    {
        printf("sentence: %c\n", sentence[i]);
    }

    /*
    for(int i = 0; i < 3; i++)
    {
            word = rand()%4;
            setence = strcat(*article, *noun );
    }*/
        return;

}

int main()
{

    char *article[5] = {"the", "a", "one", "some", "any"};
    char *noun[5] = {"boy", "girl", "dog", "town", "car"};
    char *verb[5] = {"drove", "jumped", "ran", "walked", "skipped"};
    char *preposition[5] = {"to", "from", "over", "under", "on"};
    char *holdPtr = article[0];

    srand(time(NULL));

    concatenate(*article, *noun, *verb, *preposition, holdPtr);

    return 0;

}
