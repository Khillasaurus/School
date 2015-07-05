/*
 * This program will ask the user to enter two numbers and add the numbers in the sequence until it reaches the last number and then
 * it prints out the sum of the numbers, like 1-10, 1+2+3+4+5+6+7+8+9+10= 55. if you enter a number higher than 1 for the first number
 * or lower than 1 it will find the total.
 */
import java.util.Scanner;

public class oneinfinity {


	public static void main(String[] args) {
		
	Scanner input = new Scanner(System.in);

	long count1 = 0;
	long count2 = 1;
	long total = 0;
	long total2 = 0;
	

	
System.out.println("Enter the first number");//this asks for the first number
count1=input.nextInt();
System.out.println("enter the second number");//This asks for the second number
count2 = input.nextInt();
	if(count1<count2);{
	while(count1<count2+1){ //This loop adds the numbers between count1 and count 2.
		
		
		total += count1;
		
		count1++;
		
	}
		System.out.printf("The total is %d, ", total);//This prints the total number if count1 is larger than count2.
	}
	
	if(count2<count1){ //This if statements asks if count 2 is less than count1 and changes the while loop to minus numbers instead of add.
		while(count1>count2){
			total2+= count1;
			count1--;
	}
		System.out.printf("The total is %d, ", total2);	//This prints the total number if count1 is less than count2.
	}
	
	
	
	
	
	
	
	}// end of main
	
}//end of class
