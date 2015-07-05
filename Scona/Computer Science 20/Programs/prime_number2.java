import java.util.Scanner;	//This imports a utility that reads a users input

public class prime_number2 {	//Beginning of Java Class PrimeNumber.java

	static int x = 0;
	static boolean num_type = true;
	
	public static void main(String[] args) {	//Beginning of Main
	
	Scanner input = new Scanner (System.in);	//This allows the defining of variables through user input
	
	//Assigning variables
	int num = 0;
	String composite = ("This number is composite.");
	String prime = ("This number is prime.");
	
	while(x<2147483647){
		
		System.out.println("Please enter an integer. I will then tell you if it is prime or composite.");
		
		num = input.nextInt();	//Gets user input for  variable num

		Calculations(num);
		
		if (num_type){
			System.out.println(prime);
			}
			else{
				System.out.println(composite);
				}
		
		}
	}	//End of Main
	
	public static void Calculations(int num) {
		
		for(x=2; x < num ;x++){
			int n = num%x;
			if (n==0){
			num_type = false;
			}
			break;
			}
			//Algorithm for calculating if variable num is composite or prime, then printing out result
		
		}
	
}	// End of PrimeNumber.java