////question 4.27a
//#include <stdio.h>
//
//int main()
//{
//		int testNumber;
//		bool isPrime=true;
//
//		printf("Please enter a number and I will tell you whether it is prime or not.\n");
//		scanf("%d",&testNumber);
//
//		for(int i = 2; i <= testNumber; i++)
//		{
//            for(int j = 2; j <i; j++)
//            {
//                if ( i % j == 0 )
//				{
//                    isPrime=false;
//					break;
//				}
//            }
//			if(isPrime==true && i==testNumber)
//			{
//                printf("%d is a prime number.\n",i);
//            }
//            else if(isPrime==false && i==testNumber)
//            {
//                printf("%d is not a prime number.\n",testNumber);
//                break;
//            }
//			isPrime=true;
//		}
//}



////question 4.27b
//#include <stdio.h>
//
//int main()
//{
//		int testNumber;
//		bool isPrime=true;
//
//		printf("Please enter a number and I will tell you all numbers up to and including that number that are prime.\n");
//		scanf("%d",&testNumber);
//        printf("\nPrime Numbers up to %d:\n",testNumber);
//
//		for(int i = 2; i <= testNumber; i++)
//		{
//            for(int j = 2; j <i; j++)
//            {
//                if ( i % j == 0 )
//				{
//                    isPrime=false;
//					break;
//				}
//            }
//			if(isPrime)
//			{
//                printf("%d\n",i);
//            }
//			isPrime=true;
//		}
//}




////question 4.27c
//#include <stdio.h>
//#include <math.h>
//
//int main()
//{
//		int testNumber;
//		bool isPrime=true;
//
//		printf("Please enter a number and I will tell you all numbers up to and including that number that are prime.\n");
//		scanf("%d",&testNumber);
//        printf("\nPrime Numbers up to %d:\n",testNumber);
//
//		for(int i = 2; i <= testNumber; i++)
//		{
//            for(int j = 2; j <sqrt(i); j++)
//            {
//                if ( i % j == 0 )
//				{
//                    isPrime=false;
//					break;
//				}
//            }
//			if(isPrime)
//			{
//                printf("%d\n",i);
//            }
//			isPrime=true;
//		}
//}
