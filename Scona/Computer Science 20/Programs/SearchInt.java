import java.util.Scanner;

public class SearchInt {
	public static void main(String[] args) {

		Scanner input = new Scanner (System.in);
		int [] array = new int [50];
		int number;
		boolean found = false;

		System.out.println ("Enter a number to search for int the array:");
		number = input.nextInt();

		//creating random integer array called array
		for (int x = 0; x < array.length; x++){
			array [x] = (int) (Math.random() * 100 + 1 ) ;
		} 

		//Printing the array
		System.out.println("");
		for (int y =0; y < array.length; y++){
			System.out.println(array[y]);
		}

		//search
		for (int z = 0; z <array.length; z++){
			if (number == array[z]){
				found = true;

				if(found == true){
					System.out.printf ("This number is in the array at index %d", z);
				}
				break;
			} 
		}// End of for loop 

		
			if (found == false){
				System.out.println ("Sorry! This number is not in the array.");
			
		} // End of if statement

	} // End of Method - Main
} // End of class SearchInt.java
