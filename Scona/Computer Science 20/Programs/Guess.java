/*This is a game in which you are given 10 guesses to guess a random number between 1 and 100.
*The program will tell you if your guess is oo high or too low after every guess.
*The program runs until you either win or guess 10 times, whichever comes first.
*/

import java.util.Scanner;	//This imports a utility that reads a users input
import java.util.*;	//This imports a utility that allows the creating of random numbers

public class Guess {	//Beginning of Java Class Guess.java

	public static void main(String[] args) {	//Beginning of Main

		Scanner input = new Scanner (System.in);	//This allows the defining of variables through user input
		Random randomGenerator = new Random();	//This allows the defining of variables through random computer selection
		
		//Assigning variables
		int amount = 9;
		int Amount = 0;
		int number = randomGenerator.nextInt(101);
		int guess = 0;
		String high = "Your guess is too high.";
		String low = "Your guess is too low.";
		String lose = "Sorry, you lose.";
		String congradulations = "Good job! Your guess is correct! =)";
	
		//Prints out game rules
		System.out.println("This is a game where the copmuter picks a number between 1 and 100 and you get only 10 guesses to guess it!");
		System.out.println("The computer will tell you if your guess is too high or too low also.");
		
		guess = input.nextInt();	//This reads the users input, which defines the variable guess
		
		
	//Calculates whether guess is correct or not	
	while (guess != number)							{	
		if (guess>number){
			System.out.println(high);	//Prints out String high
			Amount = amount--;
			guess = input.nextInt();
			}
	
		if (guess<number){
			System.out.println(low);	//Prints out String low
			Amount = amount--;
			guess = input.nextInt();
			}
		
		if (guess==number){
			System.out.println(congradulations);	//Prints out String congradulations
			}
		
		if (amount==0){
			System.out.println(lose);	//Prints out String lose
			break;	//Ends loop
			}
		}	//End of guess calculations
	
	}	//End of Main
}	//End of Guess.java