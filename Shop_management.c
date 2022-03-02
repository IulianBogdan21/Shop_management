#include "test.h"
#include "ui.h"
#include "shopItemVector.h"
// added for memory leak detection
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

int main()
{
	runAllTests();
	ui_consoleRun();
	_CrtDumpMemoryLeaks();
	return 0;
}