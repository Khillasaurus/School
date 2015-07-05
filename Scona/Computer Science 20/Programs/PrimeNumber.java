import java.util.Scanner;	//This imports a utility that reads a users input

public class PrimeNumber {	//Beginning of Java Class PrimeNumber.java

	public static void main(String[] args) {	//Beginning of Main

		Scanner input = new Scanner (System.in);	//This allows the defining of variables through user input

		//Assigning variables
		public static int num = 0;
		public static int x = 0;
		public static String composite = ("This number is composite.");
		public static String prime = ("This number is prime.");
		public static boolean num_type;

		while(x<2147483647){
			System.out.println("Please enter an integer. I will then tell you if it is prime or composite.");
			num = input.nextInt();
			Calculations();
			if (num_type=true){
				System.out.println(prime);
			}
			else{
				System.out.println(composite);
			}
		}
		
	}//End of Main


		public static void Calculations(num) {

			boolean num_type;

			for(x=2; x < num ;x++){
				int n = num%x;
				if (n==0){
					num_type = false;
					break;	
				}
			}
			//Algoritm for calculating if variable num is composite, if composite it will print out the result

			if (x==num){
				num_type = true;
			}
		}
		//Algorith for calculating if variable num is prime, if prime it will print out the result


}		// End of PrimeNumber.java