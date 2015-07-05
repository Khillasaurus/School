//This is a program that converts Kilometers into Miles

import java.util.Scanner;	//This imports a utility that reads a users input

public class KmToMiles {	//Beginning of Java Class KmToMiles.java

	public static void main(String[] args) {	//Beginning of Main

		Scanner input = new Scanner(System.in);	//This allows the defining of variables through user input
		
		double SundayKm, MondayKm, TuesdayKm, WednesdayKm, ThursdayKm, FridayKm, SaturdayKm;
		double SundayMiles, MondayMiles, TuesdayMiles, WednesdayMiles, ThursdayMiles, FridayMiles, SaturdayMiles;
		
	System.out.println("Enter how many kilometers you ran on Sunday.");
	SundayKm = input.nextDouble();
	SundayMiles = (SundayKm*0.621371192237334);
	/*Asks the user how many Kilometers they ran on Sunday
	*Reads the users input and assigns it to variable SundayKm
	*Converts Sunday's Kilometers to Miles
	*/
	
	System.out.println("Enter how many kilometers you ran on Monday.");
	MondayKm = input.nextDouble();
	MondayMiles = (MondayKm*0.621371192237334);
	/*Asks the user how many Kilometers they ran on Monday
	*Reads the users input and assigns it to variable MondayKm
	*Converts Monday's Kilometers to Miles
	*/
	
	System.out.println("Enter how many kilometers you ran on Tuesday.");
	TuesdayKm = input.nextDouble();
	TuesdayMiles = (TuesdayKm*0.621371192237334);
	/*Asks the user how many Kilometers they ran on Tuesday
	*Reads the users input and assigns it to variable TuesdayKm
	*Converts Tuesday's Kilometers to Miles
	*/
	
	System.out.println("Enter how many kilometers you ran on Wednesday.");
	WednesdayKm = input.nextDouble();
	WednesdayMiles = (WednesdayKm*0.621371192237334);
	/*Asks the user how many Kilometers they ran on Wednesday
	*Reads the users input and assigns it to variable WednesdayKm
	*Converts Wednesday's Kilometers to Miles
	*/
	
	System.out.println("Enter how many kilometers you ran on Thursday.");
	ThursdayKm = input.nextDouble();
	ThursdayMiles = (ThursdayKm*0.621371192237334);
	/*Asks the user how many Kilometers they ran on Thursday
	*Reads the users input and assigns it to variable ThursdayKm
	*Converts Thursday's Kilometers to Miles
	*/
	
	System.out.println("Enter how many kilometers you ran on Friday.");
	FridayKm = input.nextDouble();
	FridayMiles = (FridayKm*0.621371192237334);
	/*Asks the user how many Kilometers they ran on Friday
	*Reads the users input and assigns it to variable FridayKm
	*Converts Friday's Kilometers to Miles
	*/
	
	System.out.println("Enter how many kilometers you ran on Saturday.");
	SaturdayKm = input.nextDouble();
	SaturdayMiles = (SaturdayKm*0.621371192237334);
	/*Asks the user how many Kilometers they ran on Saturday
	*Reads the users input and assigns it to variable SaturdayKm
	*Converts Saturday's Kilometers to Miles
	*/
	

	System.out.println("Your results are:");
	System.out.printf("Sunday:" + SundayKm + " Kilometers( %.2f Miles)\n", SundayMiles);
	System.out.printf("Monday:" + MondayKm + " Kilometers( %.2f Miles)\n", MondayMiles);
	System.out.printf("Tuesday:" + TuesdayKm + " Kilometers( %.2f Miles)\n", TuesdayMiles);
	System.out.printf("Wednesday:" + WednesdayKm + " Kilometers( %.2f Miles)\n", WednesdayMiles);
	System.out.printf("Thursday:" + ThursdayKm + " Kilometers( %.2f Miles)\n", ThursdayMiles);
	System.out.printf("Friday:" + FridayKm + " Kilometers( %.2f Miles)\n", FridayMiles);
	System.out.printf("Saturday:" + SaturdayKm + " Kilometers( %.2f Miles)\n", SaturdayMiles);
	//Displays users results from the entire week in both Kilometers and Miles by using the above formula, displays Miles to 2 decimal places
	
	}	//End of Main

}	//End of KmToMiles.java
