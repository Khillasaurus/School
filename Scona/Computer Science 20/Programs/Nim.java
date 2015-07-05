/*
 * Table of Contents - Method Order
 * 1 - main
 * 2 - Rules
 * 3 - isValidEntry
 * 4 - drawStones
 */

import java.util.Random;
import java.util.Scanner;
public class Nim {

	public static Scanner input = new Scanner (System.in);
	public static Random randomGenerator = new Random();
	public static int chance1in2 = randomGenerator.nextInt(2)+1;
	public static int TotalStones = randomGenerator.nextInt(16)+15;
	public static int PlayerStones = 0;


	public static void main(String[] args) {
		Rules();

		while (TotalStones>(-1)){
			drawStones();
			if (TotalStones == 0){
				System.out.println("Congradulations! You beat the computer!");
			}
			ComputerDraw();
			if (TotalStones == 0){
				System.out.println("Aww Man! You just got WRECKED!!!");
			}
		}
	}

	public static void Rules(){

		System.out.println("This is Nim's Island.");
		System.out.println("This is a game where you verse the computer by trying to force your opponent into a losing position.");
		System.out.println("There are 15-30 stones to start.");
		System.out.println("Every turn you take 1,2 or 3 stones.");
		System.out.println("The computer will do the same.");
		System.out.println("The game ends when there are no stones left.");
		System.out.println("You do NOT want to take the last stone! (Since the person who takes the last stone loses.");
		System.out.println("");
		System.out.println("Enjoy! =)");
		System.out.println("");
	} 


	public static boolean isValidEntry(){
			if((PlayerStones >0) && (PlayerStones <4)){
				return true;
			}
			else {
				return false;
			}
	}

	public static void drawStones(){
		boolean drawOver = false;

		while(drawOver==false){
			System.out.printf("There are " + TotalStones + "stones. ");
			System.out.printf("How many would you like? ");
			PlayerStones = input.nextInt();
			System.out.println("Player Takes" + PlayerStones);
			drawOver = isValidEntry();
		}
		if(drawOver==true){
			TotalStones = (TotalStones-PlayerStones);
			System.out.printf("Player total stones is: " + TotalStones);
		}
	}

	public static void ComputerDraw(){
		boolean SmartDecision = false;
		int ComputerStones = 0;
		int RandomStones = randomGenerator.nextInt(3)+1;
		boolean isTurnOver = false;
		
		System.out.printf("The computer takes %d stones",RandomStones);
		TotalStones = TotalStones - RandomStones;
		System.out.printf("total stones is: " + TotalStones);
		
		if(TotalStones==2){
			SmartDecision = true;
		} 
		else if(TotalStones==3){
			SmartDecision = true;
		}

		//random pick
		else if ((SmartDecision==false) && (RandomStones==0)){
			ComputerStones = 1;
			isTurnOver = true;
		}
		else if((SmartDecision==false) && RandomStones==1){
			ComputerStones = 2;
			isTurnOver = true;
		}
		else if((SmartDecision==false) && RandomStones==2){
			ComputerStones = 3;
			isTurnOver = true;
		}

		//smart picking
		else if((SmartDecision==true) && (TotalStones==2)){
			ComputerStones = 1;
			isTurnOver = true;
		}
		else if((SmartDecision==true) && (TotalStones==3)){
			ComputerStones = chance1in2;
			isTurnOver = true;
		}
		else if(isTurnOver==true){
			TotalStones = (TotalStones - ComputerStones);
		}

		System.out.printf("Total Stones = " + TotalStones);
		
	}

}
