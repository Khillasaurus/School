import java.util.Scanner;	//This imports a utility that reads a users input

public class Oilers {	//Beginning of Java Class Oilers.java

	public static void main(String[] args) {
		
	//Neccesary information	
	Scanner input = new Scanner(System.in);	//This allows the defining of variables through user input

	int less10 = 0;
	int less20 = 0;
	int less30 = 0;
	int less40 = 0;
	int less50 = 0;
	int less60 = 0;
	int less70 = 0;
	int less80 = 0;
	int less90 = 0;
	int less100 = 0;
	int more100 = 0;
	int num1 = 0;
	
	
	while(num1!=-1){
		System.out.println("Enter the number of points the player got(press-1 to quit):");
		num1 = input.nextInt();
		if(num1 != -1){
			num1 = num1-(num1%10);
		}
		switch(num1){
		
			case 0:
				
				less10 = less10 + 1;
				break;
			case 10:
				
				less20 = less20 + 1;
				break;
			case 20:
				
				less30 = less30 + 1;
				break;
			case 30:
				
				less40 = less40 + 1;
				break;
			case 40:
				
				less50 = less50 + 1;
				break;
			case 50:
				
				less60 = less60 + 1;
				break;
			case 60:
				
				less70 = less70 + 1;
				break;
			case 70:
				
				less80 = less80 + 1;
				break;
			case 80:
				
				less90 = less90 + 1;
				break;
			case 90:
				
				less100 = less100 + 1;
				break;
			case 100:
				
				more100 = more100 + 1;
				break;
		}

		
	}
	System.out.println("0-10 points:"+less10);
	System.out.println("10-20 points:"+less20);
	System.out.println("20-30 points:"+less30);
	System.out.println("30-40 points:"+less40);
	System.out.println("40-50 points:"+less50);
	System.out.println("50-60 points:"+less60);
	System.out.println("60-70 points:"+less70);
	System.out.println("70-80 points:"+less80);
	System.out.println("80-90 points:"+less90);
	System.out.println("90-100 points:"+less100);
	System.out.println("100+ points:"+more100);
	}

}