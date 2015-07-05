import java.util.Scanner;

public class Fibonacci {

	public static void main(String[] args) {

		Scanner input=new Scanner(System.in);

		int number = 0;
		int value = 0;
		int again = 0;
		boolean runagain =true;

		while(runagain==true){
			System.out.println("Which number in the fibonacci sequence would you like to know?");
			number=input.nextInt();
			number=solve(number-1);
			System.out.println("The number is: "+number);
			System.out.println("Would you like to run again? (yes=1  no=0)");
			again=input.nextInt();
			if(again==1){
				runagain=true;
			}	//End if statement
			else{
				runagain=false;
			}	//End else statement
		}	//End while statement 
		System.out.println("Bye!");
	}	//End Method - main

	public static int solve(int number){

		if(number<2){
			return 1;
		}	//End if statement
		else{
			number=solve(number-1)+solve(number-2);
			return number;
		}	//End else statement
	}	//End Method - solve

}	//End class - Fibonacci.java