import java.util.Scanner;	//A utility that allows input to be taken in.

public class Necklace {	//Beginning of Java Class Necklace.java

	public static void main(String[] args) {	//Beginning of Method-Main
		
		// neccesary information
		Scanner input = new Scanner (System.in);

		//Assigning variables		
		int first = 0;
		int second = 0;
		int current = 0;
		int a = 0;
		int b = 0;
		
		first = input.nextInt();	//This reads the users input, which defines the variable first
		second = input.nextInt();	//This reads the users input, which defines the variable second
		
		a = first;
		b = second;
		
	System.out.printf("" + first + " " + second);
	
	while (current != second){
		current = a + b;
		
		if (current >= 10){
			current = current % 10;
		}
	
		System.out.printf(" " + current);
		a = b;
		b = current;
	
		}	//End of while loop
	}	//End of Main
}	//End of Necklace.java