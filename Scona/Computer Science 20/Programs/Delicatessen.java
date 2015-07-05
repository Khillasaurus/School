//This is a program that calculates deli orders over the internet for a company called Delicatessen

import java.util.Scanner;	//This imports a utility that reads a users input

public class Delicatessen {	//Beginning of Java Class Delicatessen.java

	public static void main(String[] args) {	//Beginning of Main
		
		Scanner input = new Scanner(System.in);	//This allows the defining of variables through user input

		//Assigning variables
		double tuna = 450;
		double shipping = 0;
		double overnight = 0;
		double total = 0;
		
		//Calculates the value of the variable shipping
		if (tuna>1000)shipping =300;
		else shipping=200;
		
		System.out.println("Overnight Delivery? 0=2 or more days, 1=tomorrow");
		
		overnight = input.nextInt();	//This reads the users input, which defines the variable overnight

		//Calculates the value of the variable overnight
		if (overnight>0)overnight = 500;
		else overnight = 0; 
		
		//Calculates the value of the variable total
		total=(tuna+shipping+overnight)/100;
	
		//Prints out invoice
		System.out.println("");
		System.out.println("Invoice");
		System.out.println("	Tuna Salad   $4.50");
		System.out.println("	Shipping     $"+(shipping+overnight)/100 +"0");
		System.out.println("	------------------");
		System.out.println("	Total        $" +total +"0");
	
	}	//End of Main
}	//End of Delicatessen.java