/*
 * 		Table of Contents - Methods
 * 	1 - choice
 * 	2 - display
 * 	3 - displayOne
 * 	4 - add
 * 	5 - delete
 */

/*
 * This class contains all the attributes of a CD collection and
 * provides methods to display all the CDs, add and delete CDs.
 */

// import Scanner class for input
import java.util.Arrays;
import java.util.Scanner;

public class database {

	public static Scanner input = new Scanner(System.in);

	// define the attributes of database
	String GroupName;
	String AlbumName;
	int Year;


	/* this variable keeps track of how many Albums there are.
	 * This variable is made static since it is shared by all Albums.
	 */
	public static int numberCDS = 0;

	//this constructor allows Albums to be initialized
	database(String group, String album, int year) {

		GroupName = group;
		AlbumName = album;
		Year = year;

	}	//end database data type

	// this constructor creates default or blank info
	database(){}

	/*
	 * This method asks the user what they would like to do, such as
	 * display the entire database,
	 * add a customer,
	 * or remove a customer.
	 */
	public static void choice(database db[]) {

		int choice = 0;
		String temp;
		boolean status = true;

		while(status) {

			System.out.println("This program contains all the information of the entire CD database.\n");
			System.out.println("Please choose from the following options: ");
			System.out.println("Enter 1 to display the entire collection: ");
			System.out.println("Enter 2 to add to the collection: ");
			System.out.println("Enter 3 to delete part of the collection: ");
			System.out.println("Enter 4 to sort the collection by group/artist name: ");
			System.out.println("Enter -1 to exit the program: ");
			System.out.println("Enter your selection: ");
			choice = input.nextInt();
			temp = input.nextLine();

			switch (choice) {

			case 1: 
				display(db);
				break;
			case 2: 
				database.add(db);
				break;
			case 3:
				database.delete(db);
				break;
			case 4:
				database.sort(db);
				break;
			default:
				status = false;

			}	//end switch
		} // end while
	}	//end method - choice

	/* This function will displays the entire collection, its input is an array of customers. 
	 * Instances of objects get passed to other methods just like variables do and all the attributes
	 * of those objects are passed with it.
	 */
	public static void display(database people[]) {

		// calls displayOneCustomer for each customer in the program.
		for(int i = 0; i < numberCDS; i++) {
			displayOne(people[i]);
		}	//end for i

		System.out.println("");	//prints out blank line

	}	//end method display

	
	// this function will display one Album, its parameter is to take one customer.	
	public static void displayOne(database person) {

		// this will display the Albums data on one line.
		System.out.printf("%-20s\t%-20s\t%d\n", 
				person.GroupName, person.AlbumName, person.Year);

	}	//end method displayOne

	
	// this function adds an album to the list
	public static void add(database db[]) {

		String temp;
		/*
		 * We need to get the new group/artist name, album name, and year released.
		 * 
		 * The Album is added to the end of the list.
		 */
		System.out.println("Enter the group/artist name: ");
		db[numberCDS].GroupName = input.nextLine();

		System.out.printf("Enter album name of %s: ", db[numberCDS].GroupName);
		db[numberCDS].AlbumName = input.nextLine();

		System.out.printf("Enter the year this album was released %s %s: ", 
				db[numberCDS].GroupName, db[numberCDS].AlbumName);
		db[numberCDS].Year = input.nextInt();
		temp = input.nextLine();

		numberCDS++;

	}	//end method add


	//This method removes an album from the list.
	public static void delete(database db[]) {

		// variables for group and album of element you are deleting
		String group;
		String album;

		// get the group/artist and album of the element you are deleting
		System.out.println("Enter the group/artist you want to delete: ");
		group = input.nextLine();
		System.out.println("Enter the album of the database you want to delete: ");
		album = input.nextLine();

		// search database for the album
		for(int i = 0; i<numberCDS; i++) {
			if(group.equalsIgnoreCase(db[i].GroupName) && album.equalsIgnoreCase(db[i].AlbumName)) {
				System.out.printf("Album: %s %s found!", group, album);
				System.out.println("Deleting album... ");

				/* delete the album by moving the last album in the list to the spot
				 * where the album you are deleting is and then change the number of
				 * albums to one less.
				 * 
				 * Since numberCDS is now one less, the albums data will still be store but
				 * will not be accessed because when the program searches or displays, it never
				 * looks past numberCDS.
				 */
				numberCDS--;
				db[i].GroupName = db[numberCDS].GroupName;
				db[i].AlbumName = db[numberCDS].AlbumName;
				db[i].Year = db[numberCDS].Year;


				System.out.printf("Album %s %s has been deleted!\n\n", group, album);

				// break out of the loop because we found the album
				break;
			}	//end if
		}	//end for i
		
	}	//end method delete
	
	public static void sort(database db[]){
		
		database hold;
		
		for(int x=0;x<numberCDS;x++){
			for(int y=0;y<numberCDS;y++){
				if(db[y].GroupName.compareToIgnoreCase(db[x].GroupName)>0){
					hold=db[y];
					db[y]=db[x];
					db[x]=hold;
				}	//end if
			}	//end inner for y
		}	//end outer for x
		
    }	//end method sort


}	//end class database.java
