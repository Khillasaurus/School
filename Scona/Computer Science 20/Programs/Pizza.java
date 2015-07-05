//This is a program that calculates the cost of making a pizza

import java.util.Scanner;	//This imports a utility that reads a users input

public class Pizza {	//Beginning of Java Class Pizza.java
	
	public static void main(String[]args){	//Beginning of Main
		
		Scanner input = new Scanner(System.in);	//This allows the defining of variables through user input

		double diameter = 0;  // this is the size of the pizza in inches
		int topping = 0;   // this is the number of toppings on the pizza
		double labor = 0.75;	//mandatory, labor cost is the baker's commision off the pizza
		int rent = 1;	//mandatory, rent cost is extra revenue earned by the company
		double total = 0;     // this is the total cost of he pizza
		
		System.out.println("Please enter the size of your pizza in inches.");	//Asks the user how big they want their pizza
		diameter = input.nextDouble();	//This reads the users input, which defines the variable diameter, in inches
		
		System.out.println("Please enter the amount of toppings you want on your pizza. Each topping costs $0.25.");	//Asks the user how many toppings they want their pizza
		topping = input.nextInt();	//This reads the users input, which defines the variable topping
		
		total = (0.05*diameter*diameter + 0.25*topping + rent + labor);	//This formula calculates the total cost of the pizza
		System.out.printf("The total cost of your pizza is $%.2f", total);	//This tells the user how much their pizza will cost
		                                    	                                    
	}	//End of Main
}		//End of Pizza.java