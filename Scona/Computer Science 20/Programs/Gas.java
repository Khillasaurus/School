import java.util.Scanner;	//This imports a utility that reads a users input

public class Gas {	//Beginning of Java Class Gas.java

	public static void main(String[] args) {	//Beginning of Main

		Scanner input = new Scanner(System.in);	//This allows the defining of variables through user input
		
			//Assigning variables
			double tank = 0;
			double gage = 0;
			double mpg = 0;
	
	System.out.println("Enter your tank size.");
	
	//Finds out tank size
	tank = input.nextDouble();
	
	System.out.println("Enter how full your tank is in %.");
	
	//Finds out the % of gas left in their tank
	gage = input.nextDouble();
	
	System.out.println("Enter the miles per gallon of your vehicle.");
	
	//Finds out the vehicles miles per gallon
	mpg = input.nextDouble();
	
	//Prints out a line to tell user whether they need gas or not
	if (tank*(gage/100)*mpg>=200){
		System.out.println("Safe to proceed!");
	}
	else System.out.println("Get gas!");
	
	
	}	//End of Main
}	// End of Gas.java