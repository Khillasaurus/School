//This program uses for statements to print out a cool star pattern!


public class For_Stars {	//Beginning of Java Class ForPattern.java


	public static void main(String[] args) {	//Beginning of Main
		
		//Assigning variables
		int star = 0;
		int blank = 0;
		int line = 0;
		
		
		for(line=0;line<=11;line++){	//Changes line depending on what the line number is. Bigger = more stars printed out.
			for(star=1;star<line;star++){	//Prints out # of stars depending what # the line is.
		
		System.out.printf("*");
		}
			System.out.println();
		}
		
		
		
			for(line=11;line>=2;line--){	//Same as previous line for statement except it subtracts a line rather than adding it.
				for(star=1;star<line;star++){	//Same as previous stars for loop
			
			System.out.printf("*");
			}
				System.out.println();
			}
			
		
		
			for(line=11;line>=2;line--){	//Line for statement (same as previous)
				
				for(blank=0;blank<=12-line;blank++){	//Caculates # of blanks needed in front of the stars.
					
					System.out.printf(" ");
				}
				for(star=1;star<line;star++){	//Prints out stars after the blanks.
					
					
			System.out.printf("*");
			}
				
			
				System.out.println();
			}
		
		
		
			for(line=0;line<=11;line++){	//Line for statement (same as previous)
				
				for(blank=0;blank<=12-line;blank++){	//Caculates # of blanks needed in front of the stars but in reverse order.
					
					System.out.printf(" ");
				}
				for(star=1;star<line;star++){	//Prints out stars after the blanks.
					
					
			System.out.printf("*");
			}
				
			
				System.out.println();	//Prints out a new line whenever neccesary.
			}
	
		
	}	//End of Main
}	//End of ForPattern.java