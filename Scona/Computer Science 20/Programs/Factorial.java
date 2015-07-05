/**
 * Factorial.java -
 * A recursive program to calculate the factorial of a number.
 *
 * n! = n * (n-1) * (n-2) * ... * 1
 *
 * A recursive definition of factorial is:
 *
 * n! = 1 if n <= 1
 * = n * (n-1)! if n > 2
 */
import java.util.Scanner;

public class Factorial {

	public static Scanner input = new Scanner (System.in);
	public static void main (String[] args) {

		int Number, Factorial;
		System.out.println("This program computes the factorial " + "of a number.");
		System.out.print("Enter a number: ");
		Number = input.nextInt();

		while (Number>10 || Number<1){
			System.out.print("Enter a number between 1 and 10, inclusive: ");
			Number = input.nextInt();
		}

		Factorial = factorial(Number);
		System.out.println(Number + "! = " + Factorial + ".");
	}

	/**
	 * Calculate the factorial of n.
	 *
	 * n - number to calculate factorial of.
	 * return n! - the factorial of n.
	 */
	static int factorial(int n) {

		// Base Case:
		// If n <= 1 then n! = 1.
		if (n <= 1) {
			return 1;
		}
		// Recursive Case:
		// If n > 1 then n! = n * (n-1)!
		else {
			return n * factorial(n-1);
		}
	}
}
