#include <iostream>

using namespace std;

class cPerson
{
public:
	int age;
	float height;
};

//function prototypes
void InClassMath();
void InClassClass();
int Square(const int);

int main()
{
	InClassMath();
	cout << endl;
	InClassClass();

	return 0;
}

void InClassClass()
{
	cPerson* pDaniel = new cPerson;
	cout << "How old is Daniel in years?" << endl;
	cin >> pDaniel->age;
	cout << "How tall is Daniel in cm?" << endl;
	cin >> pDaniel->height;

	cout << "Test" << endl;
	cout << "Daniel is " << pDaniel->age << " years old and " << pDaniel->height << " cm tall." << endl;
}

void InClassMath()
{
	int x = 0;
	cout << "Enter the number you would like to square." << endl;
	cin >> x;
	cout << "The square of " << x << " is " << Square(x) << "." << endl;
}

int Square(const int input)
{
	return (input*input);
}