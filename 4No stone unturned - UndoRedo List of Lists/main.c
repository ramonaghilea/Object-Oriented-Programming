#include <stdio.h>
#include "Profile.h"
#include "Repository.h"
#include "OperationStack.h"
#include "Controller.h"
#include "test.h"
#include "UI.h"
#include <crtdbg.h>

int main()
{
	Repository* newRepository = createRepository();
	DynamicArray* undoStack = createDynamicArray(DYNAMIC_ARRAY_CAPACITY, &destroyDynamicArray);
	DynamicArray* redoStack = createDynamicArray(DYNAMIC_ARRAY_CAPACITY, &destroyDynamicArray);
	Controller* newController = createController(newRepository, undoStack, redoStack);
	UI* newUI = createUI(newController);

	startUI(newUI);

	destroyUI(newUI);

	//testAll();
	_CrtDumpMemoryLeaks();

	return 0;
}