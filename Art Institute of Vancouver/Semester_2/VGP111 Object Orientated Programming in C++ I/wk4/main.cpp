// wk1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Windows.h"
#include "common/vgptime.h"
#include "common/vgptimer.h"

void TimerCode();

/*
template<class T>
class calculator
{
public:
	T Add();
	T Subtract();
protected:
	T a;
	T b;
	T Result;
	char operation = '0';
	char type = '0';
	char repeat = 'y';
};
*/

template<class T>
T Add(T a, T b)
{
	return (a + b);
}

template<class T>
T Subtract(T a, T b)
{
	return (a - b);
}

// -------------------------
int _tmain(int argc, _TCHAR* argv[])
{

	//TimerCode();

	Sint32 ia = 0;
	Sint32 ib = 0;
	float fa = 0.0f;
	float fb = 0.0f;
	Sint32 iResult = 0;
	float fResult = 0.0f;
	char operation = '0';
	char type = '0';
	char repeat = 'y';

	//Sint32 ar = Add<Sint32>(a, b);
	//float br = Add<float>(a, b);

	while ( repeat == 'y' )
	{
		while ( operation != '+' && operation != '-')
		{
			cout << "What type of operation would you like to perform?" << endl << "Enter + for addition, - for subtraction." << endl;
			cin >> operation;
		}

		while ( type != 'i' && type != 'f' )
		{
			cout << endl << "Enter an 'i' for int or an 'f' for this operation." << endl;
			cin >> type;
			if ( type == 'i' )
			{
				cout << endl << "Enter the value of a: ";
				cin >> ia;
				cout << endl << "Enter the value of b: ";
				cin >> ib;
			}
			else if ( type == 'f' )
			{
				cout << endl << "Enter the value of a: ";
				cin >> fa;
				cout << endl << "Enter the value of b: ";
				cin >> fb;
			}
		}
		if (operation == '+' && type == 'i')
		{
			iResult = Add<Sint32>(ia, ib);
			cout << endl << "iResult: " << iResult << endl;
		}
		else if (operation == '-' && type == 'i')
		{
			iResult = Subtract<Sint32>(ia, ib);
			cout << endl << "iResult: " << iResult << endl;
		}
		else if (operation == '+' && type == 'f')
		{
			fResult = Add<float>(fa, fb);
			cout << endl << "fResult: " << fResult << endl;
		}
		else if (operation == '-' && type == 'f')
		{
			fResult = Subtract<float>(fa, fb);
			cout << endl << "fResult: " << fResult << endl;
		}
		operation = '0';
		type = '0';

		cout << "Would you like to make another calculation? 'y' for yes and 'n' for no." << endl;
		cin >> repeat;
	}

	// get user's preference for type (int or float)
	// get user input
	// do requested operation
	// return result
	// repeat

	return 0;
}

void TimerCode()
{

	cTime stopTime(0,0,1);
	cTime clock; //0, 0, 0
	cTime frameTime(0,0,0,32); //32 frames per second
	cTimer timer;
	timer.Start();

	Uint32 tickCounter = 0;

	while( clock < stopTime )
	{
		++tickCounter;
		cTime elapsed = timer.GetElapsed();
		if( elapsed >= frameTime )
		{
			cTimer workTimer;
			workTimer.Start();

			clock.Add( elapsed.CalcSum() );
			clock.ToString();
			cout << "tick = " << tickCounter << endl;
			tickCounter = 0;

			workTimer.Stop();

			timer.Start();

		}
	}

	cout << "Time is up!" << endl;
	
}