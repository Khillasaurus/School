//Assignment 2 Question 3.40
#include <stdio.h>

int main()
{

    int counterA = 0;
    int counterB = 0;
    int counterC = 1;

    //Determines when to create a new line as well as modify coutner integers
    while(counterB < 8)
        {
        counterB++;

            //Create a line of asterisks in a specific pattern
            if(counterC % 2 == 0)
                {
                counterC++;
                printf(" ");
                }
                else counterC++;

            while (counterA < 8)
                {
                counterA++;
                printf("* ");
                }

        counterA = 0;
        printf("\n");
        }

    return 0;
}

////Assignment 2 Question 3.41
//#include <stdio.h>
//
//int main()
//{
//
//    int x = 2;
//
//    while(x > 1)
//        {
//        printf("%d\n" ,x);
//        x = x*2;
//        }
//
//    return 0;
//}
////When this program runs it will create an infinite loop but since it hits the memory limit for the integer data type it auto terminates due to the compiler. (I programmed this in Code::Blocks)


////Assignment 2 Question 3.42
//#include <stdio.h>
//
//int main()
//{
//
//    //Declaring variables
//    float radius;
//    float diameter;
//    float circumference;
//    float area;
//
//    //Getting user input for radius of circle
//    printf("Please enter the radius of the circle: \n");
//    scanf("%f", &radius);
//
//    //Calculations
//    diameter = radius * 2;
//    circumference = 2 * 3.14159 * radius;
//    area = 3.14159 * (radius * radius);
//
//    //Prints diameter, circumference and area of the circle
//    printf("The diamater of the circle is: %f\n" ,diameter);
//    printf("The circumference of the circle is: %f\n" ,circumference);
//    printf("The area of the circle is: %f\n" ,area);
//
//
//return 0;
//
//}


////Assignment 2 Question 3.43
//Question:
//    printf("%d", ++( x + y ) );
//Answer:
//    int z;
//    z = (x + y) + 1;
//    printf ("%d", z);


////Assignment 2 Question 3.44
//#include <stdio.h>
//
//int main()
//{
//
//    float sideA;
//    float sideB;
//    float sideC;
//    float smallSide1;
//    float smallSide2;
//    float bigSide;
//
//    printf("Please enter 3 numbers to be the sides of a triangle: \n");
//    scanf("%f%f%f" , &sideA, &sideB, &sideC);
//
//    //Check for incorrect values
//    while (sideA == 0)
//        {
//        printf("You have entered an incorrect value for side A of the traingle. Please enter a new value: \n");
//        scanf("%f" , &sideA);
//        }
//      while (sideB == 0)
//        {
//        printf("You have entered an incorrect value for side B of the traingle. Please enter a new value: \n");
//        scanf("%f" , &sideB);
//        }
//      while (sideC == 0)
//        {
//        printf("You have entered an incorrect value for side C of the traingle. Please enter a new value: \n");
//        scanf("%f" , &sideC);
//        }
//
//    //Calcluate longest side
//    if (sideA >= sideB)
//        {
//        bigSide = sideA;
//        smallSide1 = sideB;
//        smallSide2 = sideC;
//        }
//            else
//            {
//            bigSide = sideB;
//            smallSide1 =  sideA;
//            smallSide2 = sideC;
//            }
//    if (sideC >= bigSide)
//        {
//        bigSide = sideC;
//        smallSide1 = sideA;
//        smallSide2 = sideB;
//        }
//
//    //Calculate if values given can create a triangle or not and print result
//    if ( (smallSide1 + smallSide2) > bigSide)
//        {
//        printf("A triangle could be created out of these values.\n");
//        }
//            else printf("A triangle could not be created out of these values.\n");
//
//    return 0;
//
//}


////Assignment 2 Question 3.45
//#include <stdio.h>
//
//int main()
//{
//
//    float sideA;
//    float sideB;
//    float sideC;
//    float smallSide1;
//    float smallSide2;
//    float bigSide;
//    bool possible;
//
//    printf("Please enter 3 numbers to be the sides of a triangle: \n");
//    scanf("%f%f%f" , &sideA, &sideB, &sideC);
//
//    //Check for incorrect values
//    while (sideA == 0)
//        {
//        printf("You have entered an incorrect value for side A of the traingle. Please enter a new value: \n");
//        scanf("%f" , &sideA);
//        }
//      while (sideB == 0)
//        {
//        printf("You have entered an incorrect value for side B of the traingle. Please enter a new value: \n");
//        scanf("%f" , &sideB);
//        }
//      while (sideC == 0)
//        {
//        printf("You have entered an incorrect value for side C of the traingle. Please enter a new value: \n");
//        scanf("%f" , &sideC);
//        }
//
//    //Calcluate longest side
//    if (sideA >= sideB)
//        {
//        bigSide = sideA;
//        smallSide1 = sideB;
//        smallSide2 = sideC;
//        }
//            else
//            {
//            bigSide = sideB;
//            smallSide1 =  sideA;
//            smallSide2 = sideC;
//            }
//    if (sideC >= bigSide)
//        {
//        bigSide = sideC;
//        smallSide1 = sideA;
//        smallSide2 = sideB;
//        }
//
//    //Calculate if values given can create a triangle or not and print result
//    if ( (smallSide1 + smallSide2) > bigSide)
//        {
//        possible = true;
//        }
//            else
//            {
//            possible = false;
//            printf("A triangle could not be created out of these values.\n");
//            }
//
//    //Determine if values can create a right angle triangle or not and print result
//    if( ((smallSide1*smallSide1) + (smallSide2*smallSide2)) == (bigSide*bigSide) )
//        {
//        printf("A right angle traingle could be created out of these values.\n");
//        }
//            else if (possible == true)
//            {
//            printf("A traingle could be created out of these values but it is not a right angle triangle.\n");
//            }
//
//    return 0;
//
//}


////Assignment 2 Question 3.46a
//#include <stdio.h>
//
//int main()
//{
//
//    int original;
//    int digitA;
//    int digitB;
//    int digitC;
//    int digitD;
//    int digitAEncrypted;
//    int digitBEncrypted;
//    int digitCEncrypted;
//    int digitDEncrypted;
//    int storageDigit;
//    int final;
//
//    printf("Please enter a 4 digit integer.\n");
//    scanf("%d" , &original);
//
//    //Seperate digits into different single digit integers
//    digitA = original / 1000;
//    digitB = (original - (digitA * 1000)) / 100;
//    digitC = (original - (digitA * 1000) - (digitB * 100)) / 10;
//    digitD = original - (digitA * 1000) - (digitB * 100) - (digitC * 10);
//
//    //Encrypt digitA
//    digitAEncrypted = digitA + 7;
//    digitAEncrypted = digitAEncrypted%10;
//
//    //Encrypt digitB
//    digitBEncrypted = digitB + 7;
//    digitBEncrypted = digitBEncrypted%10;
//
//    //Encrypt digitC
//    digitCEncrypted = digitC + 7;
//    digitCEncrypted = digitCEncrypted%10;
//
//    //Encrypt digitD
//    digitDEncrypted = digitD + 7;
//    digitDEncrypted = digitDEncrypted%10;
//
//    //Swap Digits
//    storageDigit = digitAEncrypted;
//    digitAEncrypted = digitCEncrypted;
//    digitCEncrypted = storageDigit;
//    storageDigit = digitBEncrypted;
//    digitBEncrypted = digitDEncrypted;
//    digitDEncrypted = storageDigit;
//
//    //Calculate and print final result
//    digitAEncrypted = digitAEncrypted * 1000;
//    digitBEncrypted = digitBEncrypted * 100;
//    digitCEncrypted = digitCEncrypted *10;
//    final = digitAEncrypted + digitBEncrypted + digitCEncrypted + digitDEncrypted;
//        printf("The integer encrypted: %d\n" , final);
//
//
//    return 0;
//
//}
//
////Assignment 2 Question 3.46b
//#include <stdio.h>
//
//int main()
//{
//
//    int original = 0;
//    int digitA = 0;
//    int digitB = 0;
//    int digitC = 0;
//    int digitD = 0;
//    int digitAEncrypted = 0;
//    int digitBEncrypted = 0;
//    int digitCEncrypted = 0;
//    int digitDEncrypted = 0;
//    int storageDigit = 0;
//    int final = 0;
//
//
//    printf("Please enter a 4 digit encrypted integer.\n");
//    scanf("%d" , &original);
//
//    //Seperate digits into different single digit integers
//    digitAEncrypted = original / 1000;
//    digitBEncrypted = (original - (digitAEncrypted * 1000)) / 100;
//    digitCEncrypted = (original - (digitAEncrypted * 1000) - (digitBEncrypted * 100)) / 10;
//    digitDEncrypted = original - (digitAEncrypted * 1000) - (digitBEncrypted * 100) - (digitCEncrypted * 10);
//
//    //Un-Swap Digits
//    storageDigit = digitAEncrypted;
//    digitAEncrypted = digitCEncrypted;
//    digitCEncrypted = storageDigit;
//    storageDigit = digitBEncrypted;
//    digitBEncrypted = digitDEncrypted;
//    digitDEncrypted = storageDigit;
//
//    //De-encrypt digitA
//    digitA = digitAEncrypted + 10;
//    digitA = digitA - 7;
//    digitA = digitA%10;
//
//    //De-encrypt digitB
//    digitB = digitBEncrypted + 10;
//    digitB = digitB - 7;
//    digitB = digitB%10;
//
//    //De-encrypt digitC
//    digitC = digitCEncrypted + 10;
//    digitC = digitC - 7;
//    digitC = digitC%10;
//
//    //De-encrypt digitD
//    digitD = digitDEncrypted + 10;
//    digitD = digitD - 7;
//    digitD = digitD%10;
//
//    //Calculate and print final result
//    digitA = digitA * 1000;
//    digitB = digitB * 100;
//    digitC = digitC *10;
//
//    final = digitA + digitB + digitC + digitD;
//        printf("The integer de-encrypted: %d\n" , final);
//
//
//    return 0;
//
//}

////Assignment 2 Question 3.47a
//#include <stdio.h>
//
//int main()
//{
//
//    int original = 0;
//    int startingValue;
//    int factorial = 0;
//
//    printf("Please enter a number greater than or equal to 0: \n");
//    scanf("%d" , &original);
//
//    //Check for incorrect values
//    while (original < 0)
//    {
//        printf("You have entered an incorrect value. Please enter a number that is greater than or equal to 0: ");
//        scanf("%d" , &original);
//    }
//
//    startingValue = original;
//
//    //Calculate Factorial
//    factorial = original;
//    while (original > 1)
//    {
//    original--;
//    factorial = factorial * original;
//    }
//
//    //Exception Rule
//    if (startingValue == 0)
//        {
//        factorial = 1;
//        }
//
//    //Print out result
//    printf("The factorial of %d is %d.\n" , startingValue, factorial);
//
//
//    return 0;
//
//}

////Assignment 2 Question 3.47b
//
//#include <stdio.h>
//
//int main()
//{
//
//    float e = 1.00000;
//    int counter = 1;
//    float n = 1.00000;
//    float factorial =1.00000;
//    int accuracy = 10;
//
//
//    while (counter < accuracy)
//    {
//
//        //Calculate Factorial
//        n = counter;
//        while (n > 1)
//            {
//            factorial = factorial * n;
//            n--;
//            }
//
//        e = e + (1/factorial);
//        counter++;
//        factorial = 1;
//
//    }
//
//    //Print Result
//    printf("The approximate value of the mathematical constant e is: %f" , e);
//
//
//    return 0;
//
//}

////Could not get this to work yet, will ask you some questions on Monday's class about it and then re-submit this last question. Thanks!
////Assignment 2 Question 3.47b
//
//#include <stdio.h>
//
//int main()
//{
//
//    float e = 1.00000;
//    float counter = 1;
//    float n = 1.00000;
//    float factorial =1.00000;
//    float accuracy = 10;
//    float x = 0.00000;
//    float numerator = 1;
//
//                printf("e: %f\n" , e);
//                printf("counter: %f\n" , counter);
//                printf("n: %f\n" , n);
//                printf("factorial: %f\n" , factorial);
//                printf("accuracy: %f\n" , accuracy);
//                printf("x: %f\n" , x);
//                printf("numerator: %f\n\n" , numerator);
//
//    printf("Please enter a value for x: \n");
//    scanf("%f" , x);
//
//                printf("e: %f\n" , e);
//                printf("counter: %f\n" , counter);
//                printf("n: %f\n" , n);
//                printf("factorial: %f\n" , factorial);
//                printf("accuracy: %f\n" , accuracy);
//                printf("x: %f\n" , x);
//                printf("numerator: %f\n\n" , numerator);
//
//    while (counter < accuracy)
//    {
//
//        //Calculate Factorial
//        n = counter;
//        while (n > 1)
//            {
//            factorial = factorial * n;
//            n--;
//
//                            printf("e: %f\n" , e);
//                            printf("counter: %f\n" , counter);
//                            printf("n: %f\n" , n);
//                            printf("factorial: %f\n" , factorial);
//                            printf("accuracy: %f\n" , accuracy);
//                            printf("x: %f\n" , x);
//                            printf("numerator: %f\n\n" , numerator);
//            }
//
//        //Calculate Numerator
//        x = (counter-1);
//        while (x > 0)
//            {
//            numerator = numerator * numerator;
//            x--;
//
//
//                            printf("e: %f\n" , e);
//                            printf("counter: %f\n" , counter);
//                            printf("n: %f\n" , n);
//                            printf("factorial: %f\n" , factorial);
//                            printf("accuracy: %f\n" , accuracy);
//                            printf("x: %f\n" , x);
//                            printf("numerator: %f\n\n" , numerator);
//
//            }
//
//
//        e = e + (numerator/factorial);
//        counter++;
//        factorial = 1;
//
//                            printf("e: %f\n" , e);
//                            printf("counter: %f\n" , counter);
//                            printf("n: %f\n" , n);
//                            printf("factorial: %f\n" , factorial);
//                            printf("accuracy: %f\n" , accuracy);
//                            printf("x: %f\n" , x);
//                            printf("numerator: %f\n\n" , numerator);
//
//    }
//
//    //Print Result
//    printf("The approximate value of the mathematical constant e to the power x is: %f" , e);
//
//
//    return 0;
//
//}
