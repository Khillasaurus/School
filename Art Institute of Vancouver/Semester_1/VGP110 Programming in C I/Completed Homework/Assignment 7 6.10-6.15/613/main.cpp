//a
    Assume:char str[ 5 ];
        scanf( "%s", str ); /*User types hello*/

    /*  The reason this won't work is because the character array str is only length 5.
        The word hello is 5 characters.
        The character array str can only hold 4 characters however because the last element
        of the array is saved for the null terminator '\0'
        To fix this the code should look like the following:    */

    Assume:char str[ 6 ];
        scanf( "%s", str ); /*User types hello*/

//b
    Assume:int a[ 3 ];
        printf( "$d %d %d\n", a[ 1 ], a[ 2 ],a[ 3 ] );

    //There is a $ instead of %. It should look like:

    Assume:int a[ 3 ];
        printf( "%d %d %d\n", a[ 1 ], a[ 2 ],a[ 3 ] );

//c
    double f[ 3 ] ={ 1.1, 10.01, 100.001, 1000.0001 };

    /*  The issue here is that the array f was declared with 3 elements,
        but the user is trying to fit 4 elements inside the array.
        To fix this the code should look like the following:    */

    double f[ 4 ] ={ 1.1, 10.01, 100.001, 1000.0001 };

//d
    Assume: double d[ 2 ][ 10 ];
        d[ 1, 9 ] = 2.345;

        //The code should look like this:

    Assume: double d[ 2 ][ 10 ];
        d[ 1 ][ 9 ] = 2.345;
