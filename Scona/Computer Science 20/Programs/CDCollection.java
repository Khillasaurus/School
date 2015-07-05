//This program uses the database class to keep track of an album database
 
public class CDCollection {


	public static void main(String[] args) {

		// create a database of customers.
		database db[] = new database[50]; // assuming there are only 20 possible customers;

		/*
		 I know have to allocate space in memory for each individual album
		 because each element in the array is an object itself.
		 */
		for (int i = 0; i < 20; i++) {
			db[i] = new database();
		}	//end for

		// create 5 initial albums in the database.
		db[0] = new database("The Tragically Hip", "Day for Night", 1995);
		db[1] = new database("U2", "Best of 1990-2000", 2002);
		db[2] = new database("Lady Gaga", "The Fame", 2008);
		db[3] = new database("Michael Jackson", "Thriller", 1982);
		db[4] = new database("Linkin Park", "Hybrid Theory", 2000);
		
		for(int x = 5; x<db.length; x++){
			db[x] = new database();
		}

		database.numberCDS = 5;

		database.choice(db);

	}

}
