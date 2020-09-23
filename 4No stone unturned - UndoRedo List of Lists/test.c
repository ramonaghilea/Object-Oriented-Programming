#include "test.h"

#include <assert.h>
#include <string.h>
#include <stdio.h>


//---------------------------- Tests Profile --------------------------
void getProfileIdNumber_ValidProfile_ReturnProfileIdNumber()
{
	Profile* profile1 = createProfile(123, "DC", "def", 345);

	assert(getProfileIdNumber(profile1) == 123);

	destroyProfile(profile1);
}
void getPlaceofBirth_ValidProfile_ReturnPlaceOfBirth()
{
	Profile* profile1 = createProfile(123, "DC", "def", 345);

	assert(strcmp(getPlaceOfBirth(profile1), "DC") == 0);

	destroyProfile(profile1);
}
void getPsychologicalProfile_ValidProfile_ReturnPsychologicalProfile()
{
	Profile* profile1 = createProfile(123, "DC", "def", 345);

	assert(strcmp(getPsychologicalProfile(profile1), "def") == 0);

	destroyProfile(profile1);
}
void getYearsOfRecordedService_ValidProfile_ReturnYearsOfRecordedService()
{
	Profile* profile1 = createProfile(123, "DC", "def", 345);

	assert(getYearsOfRecordedService(profile1) == 345);

	destroyProfile(profile1);
}
void copyProfile_ValidProfile_ReturnsCopyOfProfile()
{
	Profile* profile1 = createProfile(123, "DC", "def", 345);
	Profile* profile2 = copyProfile(profile1);
	assert(getProfileIdNumber(profile1) == getProfileIdNumber(profile2));

	destroyProfile(profile1);
	destroyProfile(profile2);
}

//---------------------------- Tests Dynamic Array --------------------------

void addElement_ValidObject_AddsToArray()
{
	DynamicArray* dynamicArray = createDynamicArray(5, &destroyProfile);
	Profile* profile = createProfile(123, "DC", "def", 345);
	addElement(dynamicArray, profile);

	assert(getSize(dynamicArray) == 1);

	destroyDynamicArray(dynamicArray);
}

void deleteElement_ValidPositionOfObject_DeletesFromArray()
{
	DynamicArray* dynamicArray = createDynamicArray(5, &destroyProfile);
	Profile* profile1 = createProfile(123, "DC", "def", 345);
	Profile* profile2 = createProfile(436, "abc", "lo", 901);
	addElement(dynamicArray, profile1);
	addElement(dynamicArray, profile2);
	deleteElement(dynamicArray, 1);

	assert(getSize(dynamicArray) == 1);

	destroyDynamicArray(dynamicArray);
	destroyProfile(profile2);
}

void updateElement_ValidPositionOfObjectValidObject_UpdatesInArray()
{
	DynamicArray* dynamicArray = createDynamicArray(5, &destroyProfile);
	Profile* profile1 = createProfile(123, "DC", "def", 345);
	Profile* profile2 = createProfile(123, "abc", "lo", 901);
	addElement(dynamicArray, profile1);
	updateElement(dynamicArray, 0, profile2);

	assert(getElementByPosition(dynamicArray, 0) == profile2);

	destroyDynamicArray(dynamicArray);
	destroyProfile(profile1);
}

void getElement_ValidPositionOfObject_ReturnsObject()
{
	DynamicArray* dynamicArray = createDynamicArray(5, &destroyProfile);
	Profile* profile1 = createProfile(123, "DC", "def", 345);
	Profile* profile2 = createProfile(436, "abc", "lo", 901);
	addElement(dynamicArray, profile1);
	addElement(dynamicArray, profile2);

	assert(getElementByPosition(dynamicArray, 1) == profile2);

	destroyDynamicArray(dynamicArray);
}
void getIndexProfileByProfileIdNumber_ValidProfileIdNumber_ReturnIndexProfile()
{
	DynamicArray* dynamicArray = createDynamicArray(5, &destroyProfile);
	Profile* profile1 = createProfile(123, "DC", "def", 345);
	Profile* profile2 = createProfile(436, "abc", "lo", 901);
	addElement(dynamicArray, profile1);
	addElement(dynamicArray, profile2);

	assert(getIndexProfileByProfileIdNumber(dynamicArray, 436) == 1);

	destroyDynamicArray(dynamicArray);
}
//---------------------------- Tests Repository --------------------------

void addProfileRepository_ValidProfile_AddsToRepository()
{
	Repository* repository = createRepository();
	Profile* profile = createProfile(123, "DC", "def", 345);
	assert(addProfileRepository(repository, profile) == 0);

	destroyRepository(repository);
}

void addProfileRepository_DuplicateId_ReturnsError()
{
	Repository* repository = createRepository();
	Profile* profile = createProfile(123, "DC", "def", 345);
	addProfileRepository(repository, profile);
	assert(addProfileRepository(repository, profile) == -1);

	destroyRepository(repository);
}

void updateProfileRepository_ValidProfile_UpdatesInRepository()
{
	Repository* repository = createRepository();
	Profile* profile1 = createProfile(123, "DC", "def", 345);
	Profile* profile2 = createProfile(123, "DCAR", "defgh", 400);
	addProfileRepository(repository, profile1);
	assert(updateProfileRepository(repository, profile2) == 0);

	destroyRepository(repository);
	destroyProfile(profile1);
}

void updateProfileRepository_NonexistentId_ReturnsError()
{
	Repository* repository = createRepository();
	Profile* profile1 = createProfile(123, "DC", "def", 345);
	Profile* profile2 = createProfile(978, "DCAR", "defgh", 400);
	addProfileRepository(repository, profile1);
	assert(updateProfileRepository(repository, profile2) == -1);

	destroyRepository(repository);
	destroyProfile(profile2);
}

void deleteProfileRepository_ValidProfile_DeletesFromRepository()
{
	Repository* repository = createRepository();
	Profile* profile1 = createProfile(123, "DC", "def", 345);
	Profile* profile2 = createProfile(123, "DCAR", "defgh", 400);
	addProfileRepository(repository, profile1);
	addProfileRepository(repository, profile2);
	assert(deleteProfileRepository(repository, getProfileIdNumber(profile2)) == 0);

	destroyRepository(repository);
	destroyProfile(profile2);
}

void deleteProfileRepository_NonexistentId_ReturnsError()
{
	Repository* repository = createRepository();
	Profile* profile1 = createProfile(123, "DC", "def", 345);
	Profile* profile2 = createProfile(123, "DCAR", "defgh", 400);
	assert(deleteProfileRepository(repository, 458) == -1);

	destroyRepository(repository);
	destroyProfile(profile1);
	destroyProfile(profile2);
}

//---------------------------- Tests Controller --------------------------
void addProfileController_ValidInput_AddsToController()
{
	Repository* repository = createRepository();
	DynamicArray* undoStack = createDynamicArray(DYNAMIC_ARRAY_CAPACITY, &destroyDynamicArray);
	DynamicArray* redoStack = createDynamicArray(DYNAMIC_ARRAY_CAPACITY, &destroyDynamicArray);
	Controller* controller = createController(repository, undoStack, redoStack);

	assert(addProfileController(controller, 123, "DC", "def", 345, 0) == 0);

	destroyController(controller);
}

void addProfileController_DuplicateId_ReturnsError()
{
	Repository* repository = createRepository();
	DynamicArray* undoStack = createDynamicArray(DYNAMIC_ARRAY_CAPACITY, &destroyDynamicArray);
	DynamicArray* redoStack = createDynamicArray(DYNAMIC_ARRAY_CAPACITY, &destroyDynamicArray);
	Controller* controller = createController(repository, undoStack, redoStack);

	addProfileController(controller, 123, "DC", "def", 345, 0);
	assert(addProfileController(controller, 123, "DC", "def", 345, 0) == -1);

	destroyController(controller);
}

void updateProfileController_ValidProfile_UpdatesInController()
{
	Repository* repository = createRepository();
	DynamicArray* undoStack = createDynamicArray(DYNAMIC_ARRAY_CAPACITY, &destroyDynamicArray);
	DynamicArray* redoStack = createDynamicArray(DYNAMIC_ARRAY_CAPACITY, &destroyDynamicArray);
	Controller* controller = createController(repository, undoStack, redoStack);

	addProfileController(controller, 123, "DC", "def", 345, 0);
	assert(updateProfileController(controller, 123, "DCFG", "defGHI", 340, 0) == 0);

	destroyController(controller);
}

void updateProfileController_NonexistentId_ReturnsError()
{
	Repository* repository = createRepository();
	DynamicArray* undoStack = createDynamicArray(DYNAMIC_ARRAY_CAPACITY, &destroyDynamicArray);
	DynamicArray* redoStack = createDynamicArray(DYNAMIC_ARRAY_CAPACITY, &destroyDynamicArray);
	Controller* controller = createController(repository, undoStack, redoStack);

	addProfileController(controller, 123, "DC", "def", 345, 0);
	assert(updateProfileController(controller, 3, "DCFG", "defGHI", 340, 0) == -1);

	destroyController(controller);
}

void deleteProfileController_ValidProfile_DeletesFromController()
{
	Repository* repository = createRepository();
	DynamicArray* undoStack = createDynamicArray(DYNAMIC_ARRAY_CAPACITY, &destroyDynamicArray);
	DynamicArray* redoStack = createDynamicArray(DYNAMIC_ARRAY_CAPACITY, &destroyDynamicArray);
	Controller* controller = createController(repository, undoStack, redoStack);

	addProfileController(controller, 123, "DC", "def", 345, 0);
	assert(deleteProfileController(controller, 123, 0) == 0);

	destroyController(controller);
}

void deleteProfileController_NonexistentId_ReturnsError()
{
	Repository* repository = createRepository();
	DynamicArray* undoStack = createDynamicArray(DYNAMIC_ARRAY_CAPACITY, &destroyDynamicArray);
	DynamicArray* redoStack = createDynamicArray(DYNAMIC_ARRAY_CAPACITY, &destroyDynamicArray);
	Controller* controller = createController(repository, undoStack, redoStack);

	addProfileController(controller, 123, "DC", "def", 345, 0);
	assert(deleteProfileController(controller, 12, 0) == -1);

	destroyController(controller);
}

void undo_ValidUndo_UndoesTheLastOperation()
{
	Repository* repository = createRepository();
	DynamicArray* undoStack = createDynamicArray(DYNAMIC_ARRAY_CAPACITY, &destroyDynamicArray);
	DynamicArray* redoStack = createDynamicArray(DYNAMIC_ARRAY_CAPACITY, &destroyDynamicArray);
	Controller* controller = createController(repository, undoStack, redoStack);

	addProfileController(controller, 123, "DC", "def", 345, 0);
	assert(undo(controller) == 0);

	destroyController(controller);
}

void redo_ValidRedo_RedoesTheLastOperation()
{
	Repository* repository = createRepository();
	DynamicArray* undoStack = createDynamicArray(DYNAMIC_ARRAY_CAPACITY, &destroyDynamicArray);
	DynamicArray* redoStack = createDynamicArray(DYNAMIC_ARRAY_CAPACITY, &destroyDynamicArray);
	Controller* controller = createController(repository, undoStack, redoStack);

	addProfileController(controller, 123, "DC", "def", 345, 0);
	undo(controller);
	assert(redo(controller) == 0);

	destroyController(controller);
}

//---------------------------- Tests Operation --------------------------
void getOperationType_ValidObject_ReturnOperationType()
{
	Profile* profile1 = createProfile(123, "DC", "def", 345);
	Operation* operation = createOperation(profile1, "add");
	assert(strcmp(getOperationType(operation), "add") == 0);

	destroyOperation(operation);
	destroyProfile(profile1);
}

void getProfileOperation_ValidObject_ReturnProfileOfOperation()
{
	Profile* profile1 = createProfile(123, "DC", "def", 345);
	Operation* operation = createOperation(profile1, "add");
	assert(getProfileIdNumber(getProfileOperation(operation)) == getProfileIdNumber(profile1));

	destroyOperation(operation);
	destroyProfile(profile1);
}

//---------------------------- Tests OperationStack --------------------------
void push_ValidOperation_PushesOperationOnTheStack()
{
	Profile* profile1 = createProfile(123, "DC", "def", 345);
	Operation* operation = createOperation(profile1, "add");
	OperationsStack* operationStack = createStack();

	push(operationStack, operation);
	assert(getSizeOperationStack(operationStack) == 1);

	destroyStack(operationStack);
	destroyProfile(profile1);
}

void pop_OperationStack_PopsOperationFromTheStack()
{
	Profile* profile1 = createProfile(123, "DC", "def", 345);
	Operation* operation = createOperation(profile1, "add");
	OperationsStack* operationStack = createStack();

	push(operationStack, operation);
	assert(pop(operationStack) == operation);

	destroyStack(operationStack);
	destroyOperation(operation);
	destroyProfile(profile1);
}

void isEmpty_OperationStack_ReturnsTrue()
{
	Profile* profile1 = createProfile(123, "DC", "def", 345);
	Operation* operation = createOperation(profile1, "add");
	OperationsStack* operationStack = createStack();

	push(operationStack, operation);
	pop(operationStack);
	assert(isEmpty(operationStack) == 1);

	destroyStack(operationStack);
	destroyOperation(operation);
	destroyProfile(profile1);
}

//---------------------------- Tests GenericDynamicArray --------------------------

void addElementGeneric_GenericDynamicArray_AddsToArray()
{

	DynamicArray* arrayOfArrays = createDynamicArray(1, &destroyDynamicArray);

	// create 2 dynamic arrays of pointers to Profiles
	DynamicArray* arrayOfProfiles1 = createDynamicArray(1, &destroyProfile);
	Profile* profile1 = createProfile(123, "DC", "def", 345);
	addElement(arrayOfProfiles1, profile1);

	DynamicArray* arrayOfProfiles2 = createDynamicArray(1, &destroyProfile);
	Profile* profile2 = createProfile(978, "DCAR", "defgh", 400);
	addElement(arrayOfProfiles2, profile2);

	// add the arrays to the arrayOfArrays
	addElement(arrayOfArrays, arrayOfProfiles1);
	addElement(arrayOfArrays, arrayOfProfiles2);

	assert(getSize(arrayOfArrays) == 2);

	// this will destroy: the two profiles, the two arrays of profiles and the array of arrays
	destroyDynamicArray(arrayOfArrays);
}

void testProfile()
{
	getProfileIdNumber_ValidProfile_ReturnProfileIdNumber();
	getPlaceofBirth_ValidProfile_ReturnPlaceOfBirth();
	getPsychologicalProfile_ValidProfile_ReturnPsychologicalProfile();
	getYearsOfRecordedService_ValidProfile_ReturnYearsOfRecordedService();
	copyProfile_ValidProfile_ReturnsCopyOfProfile();
}

void testDynamicArray()
{
	addElement_ValidObject_AddsToArray();
	deleteElement_ValidPositionOfObject_DeletesFromArray();
	getElement_ValidPositionOfObject_ReturnsObject();
	updateElement_ValidPositionOfObjectValidObject_UpdatesInArray();
	getIndexProfileByProfileIdNumber_ValidProfileIdNumber_ReturnIndexProfile();
	addElementGeneric_GenericDynamicArray_AddsToArray();
}

void testRepository()
{
	addProfileRepository_ValidProfile_AddsToRepository();
	addProfileRepository_DuplicateId_ReturnsError();
	updateProfileRepository_ValidProfile_UpdatesInRepository();
	updateProfileRepository_NonexistentId_ReturnsError();
	deleteProfileRepository_ValidProfile_DeletesFromRepository();
	deleteProfileRepository_NonexistentId_ReturnsError();
}

void testController()
{
	addProfileController_ValidInput_AddsToController();
	addProfileController_DuplicateId_ReturnsError();
	updateProfileController_ValidProfile_UpdatesInController();
	updateProfileController_NonexistentId_ReturnsError();
	deleteProfileController_ValidProfile_DeletesFromController();
	deleteProfileController_NonexistentId_ReturnsError();
	undo_ValidUndo_UndoesTheLastOperation();
	redo_ValidRedo_RedoesTheLastOperation();
}

void testOperation()
{
	getOperationType_ValidObject_ReturnOperationType();
	getProfileOperation_ValidObject_ReturnProfileOfOperation();
}

void testOperationStack()
{
	push_ValidOperation_PushesOperationOnTheStack();
	pop_OperationStack_PopsOperationFromTheStack();
	isEmpty_OperationStack_ReturnsTrue();
}

void testAll()
{
	testProfile();
	testDynamicArray();
	testRepository();
	testController();
	//testOperation();
	//testOperationStack();
}
