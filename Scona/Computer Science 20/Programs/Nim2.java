/* Table of Contents - Method Order
 * 1 - main
 * 2 - Rules
 * 3 - isValidEntry
 * 4 - drawStones
 */

import java.util.Random;
import java.util.Scanner;
public class Nim2 {

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
				System.out.println("Aww Man! You just got WRECKED!!!");
				break;
			}
			ComputerDraw();
			if (TotalStones == 0){
				System.out.println("Congradulations! You beat the computer!");
				break;
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
		System.out.println("You do NOT want to take the last stone! (Since the person who takes the last stone loses)");
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
			System.out.printf("The player takes " + PlayerStones + " stones,");
			drawOver = isValidEntry();
		}
		if(drawOver==true){
			TotalStones = (TotalStones-PlayerStones);
			System.out.printf(" now there are " + TotalStones + " stones left.\n");
		}
	}

	public static void ComputerDraw(){
		boolean SmartDecision = false;
		int ComputerStones = 0;
		int RandomStones = randomGenerator.nextInt(3)+1;
		boolean isTurnOver = false;

		if(TotalStones==1){
			SmartDecision=true;
			TotalStones = TotalStones - 1;
			System.out.printf("The computer takes 1 stone,");
			System.out.printf(" now there are " + TotalStones + " left.\n");
		}
		
		else if(TotalStones==2){
			SmartDecision=true;
			TotalStones = TotalStones - 1;
			System.out.printf("The computer takes 1 stone,");
			System.out.printf(" now there are " + TotalStones + " left.\n");
		}
		
		else if(TotalStones==3){
			SmartDecision=true;
			TotalStones = TotalStones - chance1in2;
			System.out.printf("The computer takes %d stones,", chance1in2);
			System.out.printf(" now there are " + TotalStones + " left.\n");
		}
		
		
		if (SmartDecision == false){
			System.out.printf("The computer takes %d stones,",RandomStones);
			TotalStones = TotalStones - RandomStones;
			System.out.printf(" now there are " + TotalStones + " left.\n");
		}

	}

}
