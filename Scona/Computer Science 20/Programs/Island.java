// Gilligan's Island

import java.util.Scanner;	//A utility that allows input to be taken in.

public class Island {	//Beginning of Java Class Island.java

	public static void main(String[] args) {	//Beginning of Main

		// neccesary information
		Scanner input = new Scanner (System.in);
		
		//variables
			long lion = 0;
			long rhino = 0;
			long plant = 0;
			long hectare = 0;
			long year = 1;
			long guess = 0;
	
		
		//Tell user information about Gilligan's Island
			System.out.println("InfoInfoInfoInfoInfo");
		
	
		// Ask user for information about how many lions, rhino, plants and hectares they would like in there ecosystem on day one.
			System.out.println("How many lions?");
				while (lion<2)
				{
					lion = input.nextLong();
				}
			System.out.println("How many rhinos?");
				while (rhino<2)
				{
					rhino = input.nextLong();
				}
			System.out.println("How many plants?");
				plant = input.nextLong();
			System.out.println("How many hectares?");
				hectare = input.nextLong();
			System.out.println("How many years do you think your Island will last?");
				guess = input.nextInt();								
			
				while (year<11){
				
			//Calculate yearly growth/eating/sustainability
			
				//deaths
					//plant
						plant = (plant-(rhino*5000));
						
					//rhino
					rhino = (rhino-(lion*50));
						
									
				//births
					//plants
						plant = (plant*50);
						if((plant*100000)<hectare)
						{
							plant = (hectare*100000);
						}
					//rhino
						if (rhino>=2)
						{
							rhino = (rhino*6);
						}
					//lion
						if (lion>=2)
						{
							lion = (lion*2);
						}		
				
			//Calculate System - Succeed or Crash
				
				if (((lion*50)<rhino)&&((rhino*5000)<plant))
					{
					System.out.println("The amount of lions at the end of year " + year + " is:" + lion);
					System.out.println("The amount of rhinos at the end of year " + year + " is:" + rhino);
					System.out.println("The amount of plants at the end of year " + year + " is:" + plant);
					SystemSucceed();
					System.out.println("");
					}
				else {
					System.out.println("The amount of lions at the end of year " + year + " is:" + lion);
					System.out.println("The amount of rhinos at the end of year " + year + " is:" + rhino);
					System.out.println("The amount of plants at the end of year " + year + " is:" + plant);
					SystemCrash();
					System.out.println("");
					break;
				}
				
		//Display information for each year, and if system crashes, display when and why		(RESULT)
				
				year = year+1;
				}
				
	}		//End of Main

public static void SystemCrash() {
	
	System.out.println("HAHA SUCKA! EVERY1 DIES!!! MUAHAHAAAHAAAaaa hehe...!");
	
	}	//End of Method - SystemCrash

public static void SystemSucceed() {
	
	System.out.println("Good job, now what do u want? A cookie!??!");
	
}	//End of Method - Goal


}	//End of Island.java