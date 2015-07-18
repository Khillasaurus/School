/*
 * Table of Contents - Method Order
 * 		1 - main
 * 		2 - DrawGrid
 * 		3 - Player1Turn
 * 		4 - Player2Turn
 * 		5 - ComputerTurn
 * 		6 - WinGame
 */

import java.util.Random;
import java.util.Scanner;	//This imports a utility that reads a users input

public class TicTacToe {

	public static int row = 0;
	public static int coloumn = 0;
	public static int BoxesFilled = 0;
	public static Scanner input = new Scanner (System.in);
	public static Random randomGenerator = new Random();
	
	public static void main(String[] args) {
		
		//variables
		String players = "";
		String Grid[][]= new String[][]{{"[ ]", "[ ]", "[ ]"},
										{"[ ]", "[ ]", "[ ]"},
										{"[ ]", "[ ]", "[ ]"}};
		
		System.out.println("TicTacToe!!!");
		System.out.println("Player 1 is X and Player 2 or the computer is O.");
		System.out.println("Would like like to play against the computer or with a friend?");
		System.out.println("Press c for computer or f for friend.");
		
		players = input.nextLine();
		
	
		
		while(BoxesFilled<9){
			Player1Turn(Grid);
			ComputerTurn(Grid);
			System.out.printf("BoxesFilled = %d\n", BoxesFilled);
			WinGame(Grid);
			}
		
	
	if(players=="f"){
		Player1Turn(Grid);
		Player2Turn(Grid);
		System.out.printf("BoxesFilled = %d\n", BoxesFilled);
		WinGame(Grid);
	}
	
	}
	
	public static void DrawGrid(String Grid[][]){
		System.out.println(Grid[0][0] + Grid[0][1] + Grid[0][2]);
		System.out.println(Grid[1][0] + Grid[1][1] + Grid[1][2]);
		System.out.println(Grid[2][0] + Grid[2][1] + Grid[2][2]);
		}	
	
	public static void Player1Turn(String Grid[][]){
		
		System.out.println("Which row would you like to place your X in?");
		row = input.nextInt();
		System.out.println("Which coloumn would you like to place your X in?");
		coloumn = input.nextInt();
		
		if ((row == 1)&&(coloumn == 1)){
			Grid[0][0] = "[X]";
			DrawGrid(Grid);
		}
		
		if ((row == 2)&&(coloumn == 1)){
			Grid[1][0] = "[X]";
			DrawGrid(Grid);
		}
		
		if ((row == 3)&&(coloumn == 1)){
			Grid[2][0] = "[X]";
			DrawGrid(Grid);
		}
		
		if ((row == 1)&&(coloumn == 2)){
			Grid[0][1] = "[X]";
			DrawGrid(Grid);
		}
		
		if ((row == 2)&&(coloumn == 2)){
			Grid[1][1] = "[X]";
			DrawGrid(Grid);
		}
		
		if ((row == 3)&&(coloumn == 2)){
			Grid[2][1] = "[X]";
			DrawGrid(Grid);
		}
		
		if ((row == 1)&&(coloumn == 3)){
			Grid[0][2] = "[X]";
			DrawGrid(Grid);
		}
		
		if ((row == 2)&&(coloumn == 3)){
			Grid[1][2] = "[X]";
			DrawGrid(Grid);
		}
		
		if ((row == 3)&&(coloumn == 3)){
			Grid[2][2] = "[X]";
			DrawGrid(Grid);
		}
			BoxesFilled++;
			
	}
	
public static void Player2Turn(String Grid[][]){
		
		System.out.println("Which row would you like to place your X in?");
		row = input.nextInt();
		System.out.println("Which coloumn would you like to place your X in?");
		coloumn = input.nextInt();
		
		if ((row == 1)&&(coloumn == 1)){
			Grid[0][0] = "[O]";
			DrawGrid(Grid);
		}
		
		if ((row == 2)&&(coloumn == 1)){
			Grid[1][0] = "[O]";
			DrawGrid(Grid);
		}
		
		if ((row == 3)&&(coloumn == 1)){
			Grid[2][0] = "[O]";
			DrawGrid(Grid);
		}
		
		if ((row == 1)&&(coloumn == 2)){
			Grid[0][1] = "[O]";
			DrawGrid(Grid);
		}
		
		if ((row == 2)&&(coloumn == 2)){
			Grid[1][1] = "[O]";
			DrawGrid(Grid);
		}
		
		if ((row == 3)&&(coloumn == 2)){
			Grid[2][1] = "[O]";
			DrawGrid(Grid);
		}
		
		if ((row == 1)&&(coloumn == 3)){
			Grid[0][2] = "[O]";
			DrawGrid(Grid);
		}
		
		if ((row == 2)&&(coloumn == 3)){
			Grid[1][2] = "[O]";
			DrawGrid(Grid);
		}
		
		if ((row == 3)&&(coloumn == 3)){
			Grid[2][2] = "[O]";
			DrawGrid(Grid);
		}
			BoxesFilled++;
			
	}
	
	public static void ComputerTurn(String Grid[][]){
		int random = 0;
		random = randomGenerator.nextInt(9);
		boolean smart = false;
		
		System.out.println("random = " + random);
		
		
		//checking for possible player win - HORIZONTAL
		if((Grid[0][0]=="[X]")&&(Grid[0][2]=="[X]")){
			smart= true;
		}
		/*[X][ ][X]
		 *[ ][ ][ ]
		 *[ ][ ][ ]
		 */
		
		if((Grid[1][0]=="[X]")&&(Grid[1][2]=="[X]")){
			smart= true;
		}
		/*[ ][ ][ ]
		 *[X][ ][X]
		 *[ ][ ][ ]
		 */
		
		if((Grid[2][0]=="[X]")&&(Grid[2][2]=="[X]")){
			smart= true;
		}
		/*[ ][ ][ ]
		 *[ ][ ][ ]
		 *[X][ ][X]
		 */
		
		
		//checking for possible player win - VERTICAL
		if((Grid[0][0]=="[X]")&&(Grid[2][0]=="[X]")){
			smart= true;
		}
		/*[X][ ][ ]
		 *[ ][ ][ ]
		 *[X][ ][ ]
		 */
		
		if((Grid[0][1]=="[X]")&&(Grid[2][1]=="[X]")){
			smart= true;
		}
		/*[ ][X][ ]
		 *[ ][ ][ ]
		 *[ ][X][ ]
		 */
		
		if((Grid[0][2]=="[X]")&&(Grid[2][2]=="[X]")){
			smart= true;
		}
		/*[ ][ ][X]
		 *[ ][ ][ ]
		 *[ ][ ][X]
		 */
		
		
		//checking for possible player win - DIAGONAL
		if((Grid[0][0]=="[X]")&&(Grid[2][2]=="[X]")){
			smart= true;
		}
		/*[X][ ][ ]
		 *[ ][ ][ ]
		 *[ ][ ][X]
		 */
		
		if((Grid[2][0]=="[X]")&&(Grid[0][2]=="[X]")){
			smart= true;
		}
		/*[ ][ ][X]
		 *[ ][ ][ ]
		 *[X][ ][ ]
		 */
		
		
		//random placing when smart==false
		if (smart==false){
			if(random==0){
				if(Grid[0][0]!="[X]"){
				Grid[0][0]="[O]";
				}
				if(Grid[0][0]=="[X]"){
				random = randomGenerator.nextInt(9);
				}
			DrawGrid(Grid);
			BoxesFilled++;
		
		}
		
		
		else if(random==1){
			if(Grid[0][1]!="[X]"){
				Grid[0][1]="[O]";
				}
			if(Grid[0][1]=="[X]"){
				random = randomGenerator.nextInt(9);
			}
			DrawGrid(Grid);
			BoxesFilled++;
		}
		
		
		else if(random==2){
			if(Grid[0][2]!="[X]"){
				Grid[0][2]="[O]";
				}
			if(Grid[0][2]=="[X]"){
				random = randomGenerator.nextInt(9);
			}
			DrawGrid(Grid);
			BoxesFilled++;
		}
		
		
		else if(random==3){
			if(Grid[1][0]!="[X]"){
				Grid[1][0]="[O]";
				}
			if(Grid[1][0]=="[X]"){
				random = randomGenerator.nextInt(9);
			}
			DrawGrid(Grid);
			BoxesFilled++;
		}
		
		
		else if(random==4){
			if(Grid[1][1]!="[X]"){
				Grid[1][1]="[O]";
				}
			if(Grid[1][1]=="[X]"){
				random = randomGenerator.nextInt(9);
			}
			DrawGrid(Grid);
			BoxesFilled++;
		}		
		
		
		else if(random==5){
			if(Grid[1][2]!="[X]"){
				Grid[1][2]="[O]";
				}
			if(Grid[1][2]=="[X]"){
				random = randomGenerator.nextInt(9);
			}
			DrawGrid(Grid);
			BoxesFilled++;
		}
		
		
		else if(random==6){
			if(Grid[2][0]!="[X]"){
				Grid[2][0]="[O]";
				}
			if(Grid[2][0]=="[X]"){
				random = randomGenerator.nextInt(9);
			}
			DrawGrid(Grid);
			BoxesFilled++;
		}
		
		
		else if(random==7){
			if(Grid[2][1]!="[X]"){
				Grid[2][1]="[O]";
				}
			if(Grid[2][1]=="[X]"){
				random = randomGenerator.nextInt(9);
			}
			DrawGrid(Grid);
			BoxesFilled++;
		}
		
		
		else if(random==8){
			if(Grid[2][2]!="[X]"){
				Grid[2][2]="[O]";
				}
			if(Grid[2][2]=="[X]"){
				random = randomGenerator.nextInt(9);
			}
			DrawGrid(Grid);
			BoxesFilled++;
		}
		}
		System.out.println("This is the method ComputerTurn.");
		
		
		//blocking possible player win - when smart==true
		
		//blocking HORIZONTAL
		
		
		
	}
	
	public static void WinGame(String Grid[][]){
		
		
		//Horizontal Wins
		
		if((Grid[0][0]=="[X]") && (Grid[0][1]=="[X]") && Grid[0][2]=="[X]"){
			System.out.println("Player 1 wins!!! =)");
			BoxesFilled=9;
		}
		/*[X][X][X]
		 *[ ][ ][ ]
		 *[ ][ ][ ]
		 */
		
		
		if((Grid[0][0]=="[O]") && (Grid[0][1]=="[O]") && Grid[0][2]=="[O]"){
			System.out.println("Player 2 wins!!! =P");
			BoxesFilled=9;
		}
		/*[O][O][O]
		 *[ ][ ][ ]
		 *[ ][ ][ ]
		 */
		
		
		
		if((Grid[1][0]=="[X]") && (Grid[1][1]=="[X]") && Grid[1][2]=="[X]"){
			System.out.println("Player 1 wins!!! =)");
			BoxesFilled=9;
		}
		/*[ ][ ][ ]
		 *[X][X][X]
		 *[ ][ ][ ]
		 */
		
		if((Grid[1][0]=="[O]") && (Grid[1][1]=="[O]") && Grid[1][2]=="[O]"){
			System.out.println("Player 2 wins!!! =P");
			BoxesFilled=9;
		}
		/*[ ][ ][ ]
		 *[O][O][O]
		 *[ ][ ][ ]
		 */
		
		
		
		if((Grid[2][0]=="[X]") && (Grid[2][1]=="[X]") && Grid[2][2]=="[X]"){
			System.out.println("Player 1 wins!!! =)");
			BoxesFilled=9;
		}
		/*[ ][ ][ ]
		 *[ ][ ][ ]
		 *[X][X][X]
		 */
		
		if((Grid[2][0]=="[O]") && (Grid[2][1]=="[O]") && Grid[2][2]=="[O]"){
			System.out.println("Player 2 wins!!! =P");
			BoxesFilled=9;
		}
		/*[ ][ ][ ]
		 *[ ][ ][ ]
		 *[O][O][O]
		 */
		
		
		
		//Vertical Wins
		
		if((Grid[0][0]=="[X]") && (Grid[1][0]=="[X]") && Grid[2][0]=="[X]"){
			System.out.println("Player 1 wins!!! =)");
			BoxesFilled=9;
		}
		/*[X][ ][ ]
		 *[X][ ][ ]
		 *[X][ ][ ]
		 */
		
		if((Grid[0][0]=="[O]") && (Grid[1][0]=="[O]") && Grid[2][0]=="[O]"){
			System.out.println("Player 2 wins!!! =P");
			BoxesFilled=9;
		}
		/*[O][ ][ ]
		 *[o][ ][ ]
		 *[O][ ][ ]
		 */
		
		if((Grid[0][1]=="[X]") && (Grid[1][1]=="[X]") && Grid[2][1]=="[X]"){
			System.out.println("Player 1 wins!!! =)");
			BoxesFilled=9;
		}
		/*[ ][X][ ]
		 *[ ][X][ ]
		 *[ ][X][ ]
		 */
		
		if((Grid[0][1]=="[O]") && (Grid[1][1]=="[O]") && Grid[2][1]=="[O]"){
			System.out.println("Player 2 wins!!! =P");
			BoxesFilled=9;
		}
		/*[ ][O][ ]
		 *[ ][O][ ]
		 *[ ][O][ ]
		 */
		
		
		
		if((Grid[0][2]=="[X]") && (Grid[1][2]=="[X]") && Grid[2][2]=="[X]"){
			System.out.println("Player 1 wins!!! =)");
			BoxesFilled=9;
		}
		/*[ ][ ][X]
		 *[ ][ ][X]
		 *[ ][ ][X]
		 */
		
		if((Grid[0][2]=="[O]") && (Grid[1][2]=="[O]") && Grid[2][2]=="[O]"){
			System.out.println("Player 2 wins!!! =P");
			BoxesFilled=9;
		}
		/*[ ][ ][O]
		 *[ ][ ][O]
		 *[ ][ ][O]
		 */
		
		
		//Diagonal Wins
		
		if((Grid[0][0]=="[X]") && (Grid[1][1]=="[X]") && Grid[2][2]=="[X]"){
			System.out.println("Player 1 wins!!! =)");
			BoxesFilled=9;
		}
		/*[X][ ][ ]
		 *[ ][X][ ]
		 *[ ][ ][X]
		 */
		
		if((Grid[0][0]=="[O]") && (Grid[1][1]=="[O]") && Grid[2][2]=="[O]"){
			System.out.println("Player 2 wins!!! =P");
			BoxesFilled=9;
		}
		/*[O][ ][ ]
		 *[ ][O][ ]
		 *[ ][ ][O]
		 */
		
		
		
		if((Grid[2][0]=="[X]") && (Grid[1][1]=="[X]") && Grid[0][2]=="[X]"){
			System.out.println("Player 1 wins!!! =)");
			BoxesFilled=9;
		}
		/*[ ][ ][X]
		 *[ ][X][ ]
		 *[X][ ][ ]
		 */
		
		if((Grid[2][0]=="[O]") && (Grid[1][1]=="[O]") && Grid[0][2]=="[O]"){
			System.out.println("Player 2 wins!!! =P");
			BoxesFilled=9;
		}
		/*[ ][ ][O]
		 *[ ][O][ ]
		 *[O][ ][ ]
		 */
		
		
	}
	
}