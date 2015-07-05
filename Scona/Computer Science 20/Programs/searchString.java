import java.util.Scanner;

public class searchString {
	public static void main(String[] args) {

		Scanner input = new Scanner (System.in);
		String [] array = new String [10];
		String number;
		boolean found = false;
		int y = 0;

		System.out.println ("Enter a name to search for int the array:");
		number = input.nextLine();

		//creating a name array
		for (int x = 0; x < array.length; x++){
			y = x+1;
			System.out.println("Enter a name in the list. " + y + ": ");
			array [x] = input.nextLine();
		}	//End for loop

		//search
		for (int z = 0; z <array.length; z++){
			if (number.equals(array[z])){
				found = true;

				if(found == true){
					System.out.printf ("This name is in the array at index %d", z);
				}	//End (found == true) if statement
				break;
			}	//Emd (number.equals) if statement 
		}// End of for loop 

		
			if (found == false){
				System.out.println ("Sorry! This name is not in the array.");
			
		} // End of if statement

	} // End of Method - Main
} // End of class searchString.java
