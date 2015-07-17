/* Fig. 4.7: fig04_07.c
Counting letter grades */
#include <stdio.h>

/* function main begins program execution */
int main( void )
{
    int grade; /* one grade */
    int aCount = 0; /* number of As */
    int bCount = 0; /* number of Bs */
    int cCount = 0; /* number of Cs */
    int dCount = 0; /* number of Ds */
    int fCount = 0; /* number of Fs */

    printf( "Enter the letter grades.\n" );
    printf( "Enter the EOF character to end input.\n" );

    /* loop until user types end-of-file key sequence */
    while ( ( grade = getchar() ) != EOF )
    {
            if(grade == 'A' || grade == 'a')
            {
                ++aCount; /* increment aCount */
            }

            else if(grade == 'B' || grade == 'b')
            {
                ++bCount; /* increment bCount */
            }

            else if(grade == 'C' || grade == 'c')
            {
                ++cCount; /* increment cCount */
            }

            else if(grade == 'D' || grade == 'd')
            {
                ++dCount; /* increment dCount */
            }

            else if(grade == 'F' || grade == 'f')
            {
                ++fCount; /* increment fCount */
            }
    } /* end while */

    /* output summary of results */
    printf( "\nTotals for each letter grade are:\n" );
    printf( "A: %d\n", aCount ); /* display number of A grades */
    printf( "B: %d\n", bCount ); /* display number of B grades */
    printf( "C: %d\n", cCount ); /* display number of C grades */
    printf( "D: %d\n", dCount ); /* display number of D grades */
    printf( "F: %d\n", fCount ); /* display number of F grades */

    return 0; /* indicate program ended successfully */

} /* end function main */
