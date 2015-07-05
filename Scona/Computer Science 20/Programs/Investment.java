//This is a program that calculates how many years it will take the user to reach an investment value of $20000 with their current investment rate

import java.util.Scanner;	//This imports a utility that reads a users input

public class Investment {	//Beginning of Java Class Investment.java

	public static void main(String[] args) {	//Beginning of Main

		Scanner input = new Scanner (System.in);	//This allows the defining of variables through user input
		
		//Assigning variables
		double initial = 0;
		double interest = 0;
		double total = 0;
		
		System.out.println("Please enter your current investment value.");	//Gets user input for  variable initial
		initial = input.nextDouble();
		System.out.println("Please enter your current interest rate as a percentage.");	//Gets user input for  variable interest
		interest = input.nextDouble()/100;
		System.out.println("I will now calculate how long it will take you to make $20,000!");	//Gets user input for  variable total
		
		total = ((initial*interest)+initial);	//Calculates variable total
		
		while(total<20000){
			total += ((initial*interest) + interest);
			System.out.printf("%.0f years",((20000/total)+1));
			break;			
			}
			// This while loop determines what the value of the variable total will be at the end of the program
	}	//End of Main

}	//End of Investment.java