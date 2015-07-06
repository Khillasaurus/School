//-----------------------------
// File:		main.cpp
// Created:		2012/07/19
// Copyright:	Daniel Schenker
//-----------------------------

#include "stdafx.h"

//Function Prototypes
int Instructions();
void DemoVector();
void DemoList();
void DemoDeque();
void DemoMap();
void DemoMultimap();
void DemoSet();
void DemoMultiset();
void DemoStack();
void DemoQueue();
void DemoPriorityQueue();

int _tmain(int argc, _TCHAR* argv[])
{
	int choice = -1;

	while(choice != 0)
	{
		choice = Instructions();
		cout << endl << endl;

		switch(choice)
		{
			case 0:
			{
				break;
			}
			case 1:
			{
				DemoVector();
				break;
			}
			case 2:
			{
				DemoList();
				break;
			}
			case 3:
			{
				DemoDeque();
				break;
			}
			case 4:
			{
				DemoMap();
				break;
			}
			case 5:
			{
				DemoMultimap();
				break;
			}
			case 6:
			{
				DemoSet();
				break;
			}
			case 7:
			{
				DemoMultiset();
				break;
			}
			case 8:
			{
				DemoStack();
				break;
			}
			case 9:
			{
				DemoQueue();
				break;
			}
			case 10:
			{
				DemoPriorityQueue();
				break;
			}
			case 11:
			{
				cout << "Please note that all the examples use int as the templatized type." << endl;
				cout << "This does not mean that STL containers can only use int, rather it is used as an example type." << endl;
				cout << "The set of requirements needed for a templatized type to be used are called concepts." << endl;
				cout << "The concepts vary from type to type in the STL, but are based off a principle called refinement, which is similiar to inheritance." << endl;
				break;
			}
			default:
			{
				break;
			}
		}
	}

	return 0;
}

int Instructions()
{
	int choice = -1;

	do
	{
		cout << "Choose a container from the STL (Standard Template Library that you would like to view." << endl;
		cout << "1: Vector" << endl;
		cout << "2: List" << endl;
		cout << "3: Deque" << endl;
		cout << "4: Map" << endl;
		cout << "5: Multimap" << endl;
		cout << "6: Set" << endl;
		cout << "7: Multiset" << endl;
		cout << "8: Stack" << endl;
		cout << "9: Queue" << endl;
		cout << "10: Priority Queue" << endl;
		cout << "11: Information about the STL in general" << endl;
		cout << "0: Quit" << endl;
		cin >> choice;

		if(choice < 0 || choice > 11)
		{
			cout << "You have entered an incorrect value. Please enter a value between 0 and 11 inclusive." << endl;
		}
	}while(choice < 0 || choice > 11);

	cout << endl;

	return choice;
}

void DemoVector()
{
	cout << "======" << endl;
	cout << "VECTOR" << endl;
	cout << "======" << endl << endl;

	//Create vector
	cout << "Creating a vector called myVector" << endl;
	vector<int> myVector;
	cout << "Creating an interator called iter" << endl;
	vector<int>::iterator iter;

	int choice = -1;
	int value = 0;
	int location = -1;

	while(choice != 0)
	{
		do
		{
			cout << "What would you like to do?" << endl;
			cout << "1: Add an element to the end of the vector" << endl;
			cout << "2: Add an element to the beginning of the vector" << endl;
			cout << "3: Add an element to a specific location in the vector" << endl;
			cout << "4: Print the vector" << endl;
			cout << "5: Display the vector’s size" << endl;
			cout << "6: Access a particular element in the vector by using an iterator" << endl;
			cout << "7: Access a particular element in the vector by using the [] operator" << endl;
			cout << "0: Quit" << endl;
			cin >> choice;
			if(choice < 0 || choice > 7)
			{
				cout << "You have entered an incorrect value. Please enter a value between 0 and 7 inclusive." << endl;
			}
		}while(choice < 0 || choice > 7);
		cout << endl;

		switch(choice)
		{
			case 0:
			{
				return;
			}
			case 1:
			{
				cout << "Please enter the value (int) that you would like to add to the end of the vector" << endl;
				cin >> value;
				myVector.push_back(value);
				break;
			}
			case 2:
			{
				cout << "Please enter the value (int) that you would like to add to the front of the vector" << endl;
				cin >> value;
				myVector.insert(myVector.begin(), value);
				break;
			}
			case 3:
			{
				do
				{
					cout << "Where in the vector would you like to insert a value?" << endl << "Element: ";
					cin >> location;
					if(location < 0 || location > myVector.size())
					{
						cout << "You have entered an incorrect value. Please enter a value between 0 and " << (myVector.size()) << " inclusive." << endl;
					}
				}while(location < 0 || location > myVector.size());
				cout << "Please enter the value (int) that you would like to add to the vector" << endl;
				cin >> value;
				iter = myVector.begin();
				myVector.insert(iter + location, value);
				break;
			}
			case 4:
			{
				cout << "The contents of the vector: ";
				if(!myVector.empty())
				{
					for(iter = myVector.begin(); iter != myVector.end(); ++iter)
					{
						cout << *iter  << ' ';
					}
				}
				else
				{
					cout << "empty";
				}
					cout << endl;
				break;
			}
			case 5:
			{
				cout << "The size of the vector is: " << myVector.size() << endl;
				break;
			}
			case 6:
			{
				do
				{
					cout << "Which element in the vector would you like to access?" << endl;
					cin >> location;
					if(location < 0 || location > myVector.size())
					{
						cout << "You have entered an incorrect value. Please enter a value between 0 and " << (myVector.size()) << " inclusive." << endl;
					}
				}while(location < 0 || location > myVector.size());

				cout << "Element " << location << " contains the value: ";
				iter = myVector.begin();
				advance(iter, location);
				cout << *iter << endl;
				break;
			}
			case 7:
			{
				cout << "Which element in the vector would you like to access?" << endl;
				cin >> location;
				if(location < 0 || location > myVector.size())
				{
					cout << "You have entered an incorrect value. Please enter a value between 0 and " << (myVector.size()) << " inclusive." << endl;
				}
				cout << "Element " << location << " contains the value: " << myVector[location] << endl;
				break;
			}
			default:
			{
				break;
			}
		}
	}
}

void DemoList()
{
	cout << "====" << endl;
	cout << "LIST" << endl;
	cout << "====" << endl << endl;

	//Create vector
	cout << "Creating a list called myList" << endl;
	list<int> myList;
	cout << "Creating an interator called iter" << endl;
	list<int>::iterator iter;

	int choice = -1;
	int value = 0;
	int location = -1;

	while(choice != 0)
	{
		do
		{
			cout << "What would you like to do?" << endl;
			cout << "1: Add an element to the end of the list" << endl;
			cout << "2: Add an element to the beginning of the list" << endl;
			cout << "3: Add an element to a specific location in the list" << endl;
			cout << "4: Print the list using the copy algorithm and ostream iterator" << endl;
			cout << "5: Print the list using a list iterator" << endl;
			cout << "6: Display the list’s size" << endl;
			cout << "0: Quit" << endl;
			cin >> choice;
			if(choice < 0 || choice > 6)
			{
				cout << "You have entered an incorrect value. Please enter a value between 0 and 6 inclusive." << endl;
			}
		}while(choice < 0 || choice > 7);
		cout << endl;

		switch(choice)
		{
			case 0:
			{
				return;
			}
			case 1:
			{
				cout << "Please enter the value (int) that you would like to add to the end of the list" << endl;
				cin >> value;
				myList.push_back(value);
				break;
			}
			case 2:
			{
				cout << "Please enter the value (int) that you would like to add to the front of the list" << endl;
				cin >> value;
				myList.insert(myList.begin(), value);
				break;
			}
			case 3:
			{
				do
				{
					cout << "Where in the list would you like to insert a value?" << endl << "Element: ";
					cin >> location;
					if(location < 0 || location > myList.size())
					{
						cout << "You have entered an incorrect value. Please enter a value between 0 and " << (myList.size()) << " inclusive." << endl;
					}
				}while(location < 0 || location > myList.size());
				cout << "Please enter the value (int) that you would like to add to the list" << endl;
				cin >> value;
				iter = myList.begin();
				myList.insert(iter + location, value);
				cout << endl;
				break;
			}
			case 4:
			{
				ostream_iterator<int> output(cout, " ");
				copy(myList.begin(), myList.end(), output);
				cout << endl;
				break;
			}
			case 5:
			{
				cout << "The contents of the list: ";
				if(!myList.empty())
				{
					for(iter = myList.begin(); iter != myList.end(); ++iter)
					{
						cout << *iter  << ' ';
					}
				}
				else
				{
					cout << "empty";
				}
				cout << endl;
				break;
			}
			case 6:
			{
				cout << "The size of the list is: " << myList.size() << endl;
				break;
			}
			default:
			{
				break;
			}
		}
	}

}

void DemoDeque()
{
}

void DemoMap()
{
}

void DemoMultimap()
{
}

void DemoSet()
{
}

void DemoMultiset()
{
}

void DemoStack()
{
}

void DemoQueue()
{
}

void DemoPriorityQueue()
{
}