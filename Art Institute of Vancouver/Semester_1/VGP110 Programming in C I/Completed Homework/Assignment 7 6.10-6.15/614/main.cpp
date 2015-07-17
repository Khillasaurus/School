void mode( int freq[], const int answer[] )
{

	int rating; /* counter for accessing elements 1-9 of array freq */
	int j; /* counter for summarizing elements 0-98 of array answer */
	int h; /* counter for diplaying histograms of elements in array freq */
	int largest = 0; /* represents largest frequency */
	int modeValue = 0; /* represents most frequent response */

    printf( "\n%s\n%s\n%s\n",
	"********", " Mode", "********" );

	/* initialize frequencies to 0 */
	for ( rating = 1; rating <= 9; rating++ )
	{
        freq[ rating ] = 0;
    } /* end for */

	/* summarize frequencies */
	for ( j = 0; j < SIZE; j++ )
	{
        ++freq[ answer[ j ] ];
    } /* end for */

    /* output headers for result columns */
	printf( "%s%11s%19s\n\n%54s\n%54s\n\n",
	"Response", "Frequency", "Histogram",
	"1    1    2    2", "5    0    5    0    5" );

	/* output results */
	for ( rating = 1; rating <= 9; rating++ )
	{
        printf( "%8d%11d           ", rating, freq[ rating ] );
        /* keep track of mode value and largest frequency value */
        if ( freq[ rating ] > largest )
        {
            largest = freq[ rating ];
            modeValue = rating;
        } /* end if */

        /* output histogram bar representing frequency value */
        for ( h = 1; h <= freq[ rating ]; h++ )
        {
            printf( "*" );
        } /* end inner for */

    printf( "\n" ); /* being new line of output */

    } /* end outer for */

	/* display the mode value */
	printf( "The mode is the most frequent value.\n"
	"For this run the mode is %d which occurred"
	" %d times.\n", modeValue, largest );

} /* end function mode */
