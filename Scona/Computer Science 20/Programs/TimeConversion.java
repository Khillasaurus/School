// this is a program that converts time

import java.util.Scanner;	//This imports a utility that reads a users input

public class TimeConversion {	//Beginning of Java Class TimeConversion.java

	public static void main(String[]args){	//Beginning of Main
		
		Scanner input = new Scanner(System.in);	//This allows the defining of variables through user input
		
		int hours = 0;
		double minutes = 0;
		int time = 0;
	
	System.out.println("Please enter your time in minutes");
	time = input.nextInt();
	hours = (time/60);
	minutes = time % 60;
	
	System.out.println("Your time is " + hours + ":" + minutes);
	
	}//End of Main
}	//End of TimeConversion.java