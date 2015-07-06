#include <cstdlib>
#include <cstdio>

struct aStudent
{
	int age;
	float height;
};

void main()
{
	int NumStudent = 1;

	vpod* ptr = malloc(sizeof(aStudent) * NumStudents);

	int* pNumber = (int*)ptr;
	pNumber[0] = 15;
	float* pNumber = (float*)ptr;
	pfNumber[1] = 100.123;
	aStudent* pStudent = (aStudent*)ptr;;

	printf("%d %f\n", pStudent->age, pStudent->height);

	//Encrypt
	char* Encrypt = (char*) ptr;
	for(int i = 0; i < (sizeof(aStudent) * NumStudents) - 1; ++i)
	{
		Encrypt[i] = Encrypt[i+1];
	}

	printf("%d %f\n", pStudent->age, pStudent->height);

	pNumber[0] = 20;
	pfNumber[1] = 3.142;

	printf("%d %f\n", pStudent->age, pStudent->height);

	//Clean-up
	free(ptr);
	ptr = NULL;

	return 0;
}

/*
struct aStudent
{
int age;
aStudent* pNextStudent;
};
aStudent* CreateStudent( aStudent* pLastStudent, int age)
{
aStudent* pStudent = (aStudent*)malloc(sizeof(aStudent));
pStudent->age = age;
pStudent->pNextStudent = NULL;
if(pLastStudent != NULL)
{
pLastStudent->pNextStudent = pStudent;
}
return pStudent;
}
 aStudent
{
int age;
aStudent* pNextStudent;
};
aStudent* CreateStudent( aStudent* pLastStudent, int age)
{
aStudent* pStudent = (aStudent*)malloc(sizeof(aStudent));
pStudent->age = age;
pStudent->pNextStudent = NULL;
if(pLastStudent != NULL)
{
pLastStudent->pNextStudent = pStudent;
}
return pStudent;
}
int age;
aStudent* pNextStudent;
};
aStudent* CreateStudent( aStudent* pLastStudent, int age)
{
aStudent* pStudent = (aStudent*)malloc(sizeof(aStudent));
pStudent->age = age;
pStudent->pNextStudent = NULL;
if(pLastStudent != NULL)
{
pLastStudent->pNextStudent = pStudent;
}
return pStudent;
}
int age)
{
aStudent* pStudent = (aStudent*)malloc(sizeof(aStudent));
pStudent->age = age;
pStudent->pNextStudent = NULL;
if(pLastStudent != NULL)
{
pLastStudent->pNextStudent = pStudent;
}
return pStudent;
}
sizeof(aStudent));
pStudent->age = age;
pStudent->pNextStudent = NULL;
if(pLastStudent != NULL)
{
pLastStudent->pNextStudent = pStudent;
}
return pStudent;
}
if(pLastStudent != NULL)
{
pLastStudent->pNextStudent = pStudent;
}
return pStudent;
}
return pStudent;
aStudent* pStudent = NULL;
aStudent* pFirstStudent = NULL;
int a = 0;
do
int a = 0;
do
do
{
pStudent = CreateStudent(pStudent, a);
if(pFirstStudent == NULL)
{
pFirstStudent = pStudent;
}
a++;
}while(a < 10);
while(1);
if(pFirstStudent == NULL)
{
pFirstStudent = pStudent;
}
a++;
}while(a < 10);
while(1);
while(a < 10);
while(1);
while(1);
}

*/