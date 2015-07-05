//

import java.util.Scanner;	//A utility that allows input to be taken in.

public class maxMIN {	//Beginning of Java Class maxMIN.java
	
	public static void main(String[] args) {	//Beginning of Method-Main
		
		// neccesary information
		Scanner input = new Scanner (System.in);
		
		double a = 0;
		double b = 0;
		double c = 0;
		double d = 0;
		
		double GradesMax = 0;
		double GradesTotal = 0;
		double GradesAverage = 0;
		
		a = input.nextDouble();
		b = input.nextDouble();
		c = input.nextDouble();
		d = input.nextDouble();

		GradesTotal = max(a, b, c, d);
		GradesTotal = min(a, b, c, d);
		GradesTotal = sum(a, b, c, d);
		GradesAverage = average(a,b,c,d);
		
		
		}	//End of Method-main

	public static double max(double a, double b, double c, double d){	//Beginning of Method-max
		
		double result = 0;
		
			if(a>b){
				result = a;
			}
				else {
					result = b;
				}
			if(c>result){
			result = c;
			}
			if(d>result){
			result = d;
			}
			
			System.out.println("The biggest number is: " + result);
			
			return result;
					
	}	//End of Method-max
	
	public static double min(double a, double b, double c, double d){	//Beginning of Method-min
		
		double result = 0;
		
		if(a<b){
			result = a;
		}
			else {
				result = b;
			}
		if(c<result){
		result = c;
		}
		if(d<result){
		result = d;
		}
		
		System.out.println("The smallest number is: " +result);
		
		return result;
		
	}	//End of Method-min

	public static double sum(double a, double b, double c, double d){	//Beginning of Method-sum

		double result = 0;
		
		result = (a + b + c + d);
		
		System.out.println("The sum of all the numbers is: " + result);
		
		return result;
		
	}	//End of Method-sum

	public static double average(double sum){	//Beginning of Method-average
			
		double result;
		result = sum/4;
		
		return result;
		
	}	//End of Method-average
	
	public static double average(double a, double b, double c, double d){	//Beginning of Method-average
		
		double result;
		result = sum(a,b,c,d)/4;
		
		return result;
		
	}	//End of Method-average
	
}	//End of class
