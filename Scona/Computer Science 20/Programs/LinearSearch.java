/*
 * 		Table of Contents - Methods
 * 	1 - main
 * 	2 - sort
 * 	3 - search
 * 	4 - displaylist
 */

import java.util.Random;
import java.util.Scanner;

public class LinearSearch {

	public static int nElems;

	public static Scanner input = new Scanner (System.in);
	public static Random randomGenerator = new Random();

	public static void main(String[] args) {

		int list[] = new int[100];

		for(int x = 0; x<list.length; x++){
			list[x] = randomGenerator.nextInt(100)+1;
		}	//End for loop

		System.out.printf("Jumbled list of 100 integers from 1 to 100, inclusive.\n\n");
		displaylist(list);
		System.out.println();
		
		System.out.printf("Sorted version of list.\n\n");
		sort(list);
		displaylist(list);

	}	//End of Method - main


	public static void sort(int list[]){

		int out, in;

		for(out=nElems-1; out>1; out--)  // outer loop (backward)
			for(in=0; in<out; in++)    // inner loop (forward)
				if( list[in] > list[in+1] )    // checking order
					swap(in, in+1,list);     // swap them

	}	//End of Method - sort


	public static void swap(int one, int two, int list[])
	{
		int temp = list[one];
		list[one] = list[two];
		list[two] = temp;
	}


	public static void search(int list[]){

		int search, index = 0;
		System.out.println("Enter the number you would likt to search for:");
		search = input.nextInt();

		for(int a=0; a<list.length; a++){
			index = a;
			break;
		}	//End for statement

		System.out.println("The number " + search + " is at index " + index + ".");

	}	//End of Method - search


	public static void displaylist(int list[]){

		for(int x = 0; x<list.length; x++){
			System.out.println(list[x]);
		}

	}	//End of Method - displaylist

}	//End of class - LinearSearch.java





