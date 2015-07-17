#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "common/vgptime.h"
#include "common/vgptimer.h"
#include <vector>
#include <list>
#include <map>
#include <assert.h>
#include <crtdbg.h>
#include "tAutoRef.h"
#include "object.h"


int _tmain(int argc, _TCHAR* argv[])
{

	{
		tAutoRef<cPotato> pPotato = new cPotato;
	}
	
	system( "pause" );

	return 0;
}
