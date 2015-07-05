////Assigment 4.25
//#include <stdio.h>
//
//int main()
//{
///*
//int p = 0;
//int answer:
//use specifiers %o is octals for example, hex is %h
//
//13 to binary
//
//13/2	q=6		r=1
//answer += pow(10,p)*r
//p++;
//6/2		q=3		r=0
//3/2		q=1		r=1
//1/2		q=0		r=1
//stop when q=0. answer is in reverse, so ansewr is 1101
//*/
//
//
//return 0;
//
//}
//
//
//
//
////Assignment 4.26
//#include <stdio.h>
//
//int main()
//{
//	
///*
//if pi equals 3.14, any number from 3.135 to 3.144 rounds to 3.14
//if pi equals 3.141, lower limit is 3.1405, upper limit is 3.1414
//*/
//
//return 0;
//
//}
//
//
//
//
////Assignment 4.27
//#include <stdio.h>
//
//int main()
//{
//
//
//
//return 0;
//
//}
//
//
//
//
////Assignment 4.28
//#include <stdio.h>
//
//int main()
//{
//
////switch case or if else
//
//return 0;
//
//}
//
//
//
//
////Assignment 4.29
//
////De Morgan's Law !(A&&B) == !A||!B
//A)	Q.	!(x<5) && !(y>=7)
//	A.	!((x<5) || (y>=7))
//B)	Q.	!(a==b) || !(g!=5)
//	A.	!((a==b) && (g!=5))
//C)	Q.
//	A.
////don't need to write program for this, just write write text form of answers
//
//
//
//
//
////Assignment 4.30
//#include <stdio.h>
//
//int main()
//{
//
//
//
//return 0;
//
//}

#include "stdafx.h"
#include <stdio.h>

int main()
{

    float e = 1.00000; //the value of the variable 'e' in the equation
	float x = 0.00000; //the value of the variable 'x' in the equation
	float i = 1.00000; //the power of 'x' in the equation

	float numerator = 1.00000; //the value of the numerator of the equation
    float factorial =1.00000; //the value of the denominator in the equation

	int counter = 1; //a counter to determine which addition step the formula is calulating
    int accuracy = 10; //a limiter placed on the supposed-to-be never ending loop to prevent values from exceeding the maximum value for a float data type

	float n = 1.00000; //same thing as counter except this variable is modified due to calculations (to prevent the changing of the variable counter)

				printf("First.\n");
                printf("e: %f\n" , e);
				printf("x: %f\n" , x);
				printf("i: %f\n" , i);
				printf("numerator: %f\n" , numerator);
				printf("factorial: %f\n" , factorial);
                printf("counter: %d\n" , counter);
				printf("accuracy: %d\n" , accuracy);
                printf("n: %f\n\n" , n);
                
                

    printf("Please enter a value for x: \n");
    scanf("%f" , &x);

	numerator = x; //sets first numerator to 1

				printf("Second.\n");
                printf("e: %f\n" , e);
				printf("x: %f\n" , x);
				printf("i: %f\n" , i);
				printf("numerator: %f\n" , numerator);
				printf("factorial: %f\n" , factorial);
                printf("counter: %d\n" , counter);
				printf("accuracy: %d\n" , accuracy);
                printf("n: %f\n\n" , n);

    while (counter < accuracy)
    {
		numerator = x;

		//Calculate Numerator
				i = (counter-2);
				while (i > 0)//multiply the value of 'x' i times
					{
					numerator = numerator * numerator;
					i--;


									printf("Third.\n");
									printf("e: %f\n" , e);
									printf("x: %f\n" , x);
									printf("i: %f\n" , i);
									printf("numerator: %f\n" , numerator);
									printf("factorial: %f\n" , factorial);
									printf("counter: %d\n" , counter);
									printf("accuracy: %d\n" , accuracy);
									printf("n: %f\n\n" , n);

					}

        //Calculate Factorial
        n = counter;
        while (n > 1)
            {
            factorial = factorial * n;
            n--;

							printf("Fourth.\n");
                            printf("e: %f\n" , e);
							printf("x: %f\n" , x);
							printf("i: %f\n" , i);
							printf("numerator: %f\n" , numerator);
							printf("factorial: %f\n" , factorial);
							printf("counter: %d\n" , counter);
							printf("accuracy: %d\n" , accuracy);
							printf("n: %f\n\n" , n);
            }

        


		//Calculate current term
        e = e + (numerator/factorial);
        counter++;

							printf("Fifth.\n");
                            printf("e: %f\n" , e);
							printf("x: %f\n" , x);
							printf("i: %f\n" , i);
							printf("numerator: %f\n" , numerator);
							printf("factorial: %f\n" , factorial);
							printf("counter: %d\n" , counter);
							printf("accuracy: %d\n" , accuracy);
							printf("n: %f\n\n" , n);

    }

    //Print Result
    printf("The approximate value of the mathematical constant e to the power x is: %f" , e);


    return 0;

}
