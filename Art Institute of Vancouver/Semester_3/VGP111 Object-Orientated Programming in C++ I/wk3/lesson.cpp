#include "stadfx.h"

class cBla
{
public:
	cBla operator << (int x)
	{
		mx += x;

		return cBla();
	}
	int mx;
};

void LessonWeek3()
{

}