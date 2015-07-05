// Imperial to Metric

import java.util.Scanner;	//A utility that allows input to be taken in.

public class Conversion {	//Beginning of Java Class Conversion.java

	//variables
		//other
		static double value = 0;
		static int choice = 0;
		static int y = 1;
		static int z = 2;
	
	public static void main(String[] args) {	//Beginning of Method-Main

		// neccesary information
		Scanner input = new Scanner (System.in);
			
			while (y!=z)
			{
		//Get input
			System.out.println("Choose an option.");
			System.out.printf("1:inches to centimeters.\n 2:feet to centimeters.\n 3:yards to meters.\n 4:miles to kilometers.\n 5:centimeters to inches.\n 6.centimeters to feet.\n 7:meters to yards.\n 8:kilometers to miles.\n");
			choice = input.nextInt();
			System.out.println("Type the number you would like to convert, decimal places are allowed.");
			value = input.nextDouble(); 
			
			if (choice==1)
			{
				one();
			}
				 
			if (choice==2)
			{
				two();
			} 
			
			if (choice==3)
			{
				three();
			}
			
			if (choice==4)
			{
				four();
			}
			
			if (choice==5)
			{
				five();
			}
			
			if (choice==6)
			{
				six();
			}
			
			if (choice==7)
			{
				seven();
			}
			 
			if (choice==8)
			{
				eight();
			}
		
		}	//End of while loop
			
	}	//End of Method-Main

	public static void one(){	//Beginning of Method-one
		value = (value*2.54);
		System.out.println(value + "cm");
	}	//End of Method-one
	
	public static void two(){	//Beginning of Method-one
		value = (value*30);
		System.out.println(value + "cm");
	}	//End of Method-one
	
	public static void three(){	//Beginning of Method-one
		value = (value*0.91);
		System.out.println(value + "m");
	}	//End of Method-one
	
	public static void four(){	//Beginning of Method-one
		value = (value*1.6);
		System.out.println(value + "km");
	}	//End of Method-one
	
	public static void five(){	//Beginning of Method-one
		value = (value/2.54);
		System.out.println(value + "in");
	}	//End of Method-one
	
	public static void six(){	//Beginning of Method-one
		value = (value/30);
		System.out.println(value + "ft");
	}	//End of Method-one
	
	public static void seven(){	//Beginning of Method-one
		value = (value-0.91);
		System.out.println(value + "yards");
	}	//End of Method-one
	
	public static void eight(){	//Beginning of Method-one
		value = (value/1.6);
		System.out.println(value + "mi");
	}	//End of Method-one
	
}	//End of class Conversion.java
