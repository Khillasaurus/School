/*
 * Table of Contents - Method Order
 * 		1 - main
 * 		2 - Play
 * 		3 - Bet
 * 		4- DisplayCard
 * 		5 - HitMe
 * 		6 - Bust
 * 		7 - Result
 */

import java.util.*;	//A utility that allows input to be taken in.

public class Blackjack {

	//necessary variables
	public static Scanner input = new Scanner (System.in);
	public static Random randomGenerator = new Random();
	
	//more variables
	public static double money = 500.00;
	public static int card = randomGenerator.nextInt(10)+1;
	public static double CurrentBet = 0;
	
	public static void main(String[] args) {	//Beginning of Method - Main
		
		String decision;
		
		Play();
		DisplayCard();
		System.out.println("h = Hit or s = Stay?");
		decision = input.nextLine();
		
		if (decision.equalsIgnoreCase("h")){
			HitMe();
		}
		
		if (decision.equalsIgnoreCase("s")){
			Result();
		}
		
	}	//End of Method-main

	
	public static void Play () {
		String yesORno;
		
		System.out.println("Would you like to play Blackjack?");
		System.out.println("y = yes, n = no");
		yesORno = input.nextLine();
		
		System.out.println(yesORno);
		
		while (yesORno.equalsIgnoreCase("n")){
		System.out.println("Are you sure? y to play, n to be bored");
		yesORno = input.nextLine();
		}
		
		if (yesORno.equalsIgnoreCase("y")){
			System.out.printf("You have $%.2f\n", money);
			Bet();
			
		}
		
		
	}	//End of Method - Play
	
	
public static void Bet () {
	
	System.out.println("How much would you like to bet?");
	CurrentBet = input.nextDouble();
	
	while (CurrentBet <1){
		System.out.println("Uhm, no1 plays 4 free here man...");
		System.out.println("PUT SOME MONEY DOWN!!! and make it LEGIT XD");
		System.out.println("How much would you like to bet?");
		CurrentBet = input.nextDouble();
	}
	
	while (CurrentBet >money){
		System.out.println("Woah hey, no bluffing, CHEATER!");
		System.out.println("How much would you like to bet?");
		CurrentBet = input.nextDouble();
	}
	
	}	//End of Method - Bet
	

	public static void DisplayCard() {
		
		System.out.println("I will now deal the cards.");
		System.out.println(card);
		
		
	}

	public static void HitMe () {
		
	}	//End of Method - HitMe
	
	public static void Bust() {
		
	}
	
	public static void Result () {

	}
		
}	//End of Blackjack.java
