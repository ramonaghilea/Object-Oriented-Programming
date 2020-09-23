#include "Controller.h"
#include "Repository.h"
#include "UI.h"
#include <crtdbg.h>
#include <iostream>
#include <fstream>

int main()
{
	{
		Repository repository;
		Controller controller{ repository };
		UI ui{ controller };

		ui.start();
	}

	// _CrtDumpMemoryLeaks();

	return 0;
}