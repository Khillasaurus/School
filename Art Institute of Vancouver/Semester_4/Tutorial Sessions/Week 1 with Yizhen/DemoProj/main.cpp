//============================================================================
// C++ Class explained
//============================================================================
// encapsulation // 3 ps, public interfaces
// inheritance	// 3 ps, 


// polymorphism	// virtual functions, virtual table,


#include <iostream>
using namespace std;

// interface class, and typically it's "abstract"
class Car
{
public:
	virtual void Drive()
	{
		cout << "I am the base car, the Drive() feature is not defined" << endl;
	};
};//---------------------------------------------------------------------------------------------------------


class Toyota : public Car
{
public:
	void Drive()
	{
		cout << "Speed at 80 km/hr" << endl;
	};
};

class Ferrari : public Car
{
public:
	void Drive() 
	{
		cout << "Speed at 280 km/hr" << endl;
	};
};


class Enemy
{
public:
	virtual void Attack() = 0;
};

class EnemyA : public Enemy
{
public:
	virtual void Attack()
	{
		cout << "gives damage 10" <<endl;
	}
};

class EnemyB : public Enemy
{
public:
	virtual void Attack()
	{
		cout << "gives damage 100" <<endl;
	}
};


void main()
{
	Enemy* enemiesOfAllTypes[200] = {NULL}; 
	// instantiate object
	enemiesOfAllTypes[0] = new EnemyA();
	enemiesOfAllTypes[1] = new EnemyB();





	enemiesOfAllTypes[0]->Attack();





	Car* pCar = NULL;

	pCar = new Toyota();
	pCar->Drive();

	pCar = new Ferrari();
	pCar->Drive();


	// polymorphysm means, you can do different things with a same pointer type.
}