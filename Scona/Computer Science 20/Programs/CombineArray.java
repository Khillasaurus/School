/*
 * 		Table of Contents - Methods
 * 	1 - main
 * 	2 - sortlist
 * 	3 - Combine
 * 	4 - DISPLAYlist1
 * 	5 - DISPLAYlist2
 * 	6 - DISPLAYllistfinal
 */

import java.util.Random;
import java.util.Scanner;

public class CombineArray {

	public static int nElems1;
	public static int nElems2;

	public static Scanner input = new Scanner (System.in);
	public static Random randomGenerator = new Random();



	public static void main(String[] args) {

		int list1[] = new int[50];
		int list2[] = new int[150];
		int listfinal[] = new int[200];

		for(int x = 0; x<list1.length; x++){
			list1[x] = randomGenerator.nextInt(100)+1;
		}	//End for loop

		for(int x = 0; x<list2.length; x++){
			list2[x] = randomGenerator.nextInt(100)+1;
		}	//End for loop

		System.out.println("Creates two lists.");
		System.out.println("First list has 50 elements:");
		DISPLAYlist1(list1);
		System.out.println();
		System.out.println("Second list has 150 elements:");
		DISPLAYlist2(list2);
		System.out.println();

		System.out.println("Sorting list 1:");
		sortlist(list1);
		DISPLAYlist1(list1);
		System.out.println();
		System.out.println("Sorting list 2:");
		sortlist(list2);
		DISPLAYlist2(list2);

		Combine(list1, list2, listfinal);


	}	//End method - main



	public static void sortlist(int [] x) {
		for (int i=0; i<x.length-1; i++) {
			for (int j=i+1; j<x.length; j++) {
				if (x[i] > x[j]) {
					//swapping elements
					int temp = x[i];
					x[i] = x[j];
					x[j] = temp;
				}	//End if statement
			}	//End inner for loop
		}	//End outer for loop
	}	//End method - sortlist



	public static void Combine(int list1[], int list2[], int listfinal[]){

		int i = 0;
		int j = 0;
		int k = 0;
		
		System.out.println("Combining the two lists...");
		while (i<list1.length && j<list2.length){
			
			if(list1[i] < list2[j]) {
				listfinal[k] = list1[i];
				i++;
				k++;
			}	//end if
			else {
				listfinal[k] = list2[j];
				j++;
				k++;
			}	//end else
			
		}	//end while

		// Empty the list that is not empty
		
		while (i>=list1.length && k<listfinal.length && j<list2.length){
			listfinal[k] = list2[j];
			k++;
			j++;
		}	//end while
		
		while (j>=list2.length && k<listfinal.length && i<list1.length){
			listfinal[k] = list1[i];
			k++;
			i++;
		}	//end while
		
		System.out.println("Displaying the combined list:");
		DISPLAYlistfinal(listfinal);

	}	//End method - Combine



	public static void DISPLAYlist1(int list1[]){

		for(int a = 0; a<list1.length; a++){
			System.out.println(list1[a]);
		}	//End for loop

	}	//End method - DISPLAYlist1

	public static void DISPLAYlist2(int list2[]){

		for(int a = 0; a<list2.length; a++){
			System.out.println(list2[a]);
		}	//End for loop

	}	//End method - DISPLAYlist2



	public static void DISPLAYlistfinal(int listfinal[]){

		for(int a = 0; a<listfinal.length; a++){
			System.out.println(listfinal[a]);
		}	//End for loop

	}	//End method - DISPLAYlist2



}	//End class - CombineArray.java
