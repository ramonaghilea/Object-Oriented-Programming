#include "Controller.h"
#include <stdlib.h>
#include <string.h>

Controller* createController(Repository* repository, OperationsStack* undoStack, OperationsStack* redoStack)
{
	Controller* newController = (Controller*)malloc(sizeof(Controller));
	if (newController == NULL)
		return NULL;

	newController->repository = repository;
	newController->undoStack = undoStack;
	newController->redoStack = redoStack;

	return newController;
}

void destroyController(Controller* controller)
{
	destroyRepository(controller->repository);
	destroyStack(controller->undoStack);
	destroyStack(controller->redoStack);

	free(controller);
}

int addProfileController(Controller* controller, int profileIdNumber, char* placeOfBirth, char* psychologicalProfile, int yearsOfRecordedService, int duringUndo)
{
	int resultOfOperation;
	Profile* newProfile = createProfile(profileIdNumber, placeOfBirth, psychologicalProfile, yearsOfRecordedService);

	resultOfOperation = addProfileRepository(controller->repository, newProfile);
	if (resultOfOperation == 0 && duringUndo == 0) //the operation was done successfully, register the operation
	{
		Operation* undoOperation = createOperation(newProfile, "delete"); //the reverse of add is delete
		push(controller->undoStack, undoOperation);
	}
	if (!duringUndo)
	{
		// a redo cand be performed only after an undo
		clearStack(controller->redoStack);
	}

	return resultOfOperation;
}

int updateProfileController(Controller* controller, int profileIdNumber, char* newPlaceOfBirth, char* newPsychologicalProfile, int newYearsOfRecordedService, int duringUndo)
{
	int resultOfOperation;
	Profile* newProfile = createProfile(profileIdNumber, newPlaceOfBirth, newPsychologicalProfile, newYearsOfRecordedService);

	Profile* oldProfile = getProfileByIdNumber(controller->repository, getProfileIdNumber(newProfile));

	resultOfOperation = updateProfileRepository(controller->repository, newProfile);

	if (resultOfOperation == 0 && duringUndo == 0) //the operation was done successfully and we are not durin undo, register the operation
	{
		Operation* undoOperation = createOperation(oldProfile, "update");
		push(controller->undoStack, undoOperation);
	}
	if (!duringUndo)
	{
		// a redo cand be performed only after an undo
		clearStack(controller->redoStack);
	}
	if (resultOfOperation == 0)
	{
		destroyProfile(oldProfile); /////CHANGE
	}
	else
	{
		destroyProfile(newProfile);
	}
		//destroyProfile(oldProfile); /////CHANGE

	return resultOfOperation;
}

int deleteProfileController(Controller* controller, int profileIdNumber, int duringUndo)
{
	int resultOfOperation;
	Profile* newProfile = getProfileByIdNumber(controller->repository, profileIdNumber);

	resultOfOperation = deleteProfileRepository(controller->repository, profileIdNumber);
	if (resultOfOperation == 0 && duringUndo == 0) //the operation was done successfully, register the operation
	{
		Operation* undoOperation = createOperation(newProfile, "add"); //the reverse of add is delete
		push(controller->undoStack, undoOperation);
	}
	if (!duringUndo)
	{
		// a redo cand be performed only after an undo
		clearStack(controller->redoStack);
	}

	if (resultOfOperation == 0)
	{
		destroyProfile(newProfile); /////CHANGE
	}
	//destroyProfile(newProfile); /////CHANGE
	return resultOfOperation;
}

int getNumberProfilesController(Controller* controller)
{
	return getNumberProfiles(controller->repository);
}

int undo(Controller* controller)
{
	// if the undoStack is empty, return an error
	if (isEmpty(controller->undoStack))
	{
		return -1;
	}

	Operation* operation = pop(controller->undoStack);

	if (strcmp(getOperationType(operation), "add") == 0)
	{
		Profile* profile = getProfileOperation(operation);
		// create the reverse operation for redo
		Operation* redoOperation = createOperation(profile, "delete");
		// push it to the redo stack
		push(controller->redoStack, redoOperation);
		int duringUndo = 1;
		addProfileController(controller, getProfileIdNumber(profile), getPlaceOfBirth(profile), getPsychologicalProfile(profile), getYearsOfRecordedService(profile), duringUndo);
	}
	else if (strcmp(getOperationType(operation), "update") == 0)
	{
		Profile* profile = getProfileOperation(operation); //the old profile
		// create the reverse operation for redo
		// we should memorize the currentProfile, which has the same IdNumber as the one from the undoStack operation
		Profile* currentProfile = getProfileByIdNumber(controller->repository, getProfileIdNumber(profile));
		Operation* redoOperation = createOperation(currentProfile, "update");
		// push it to the redo stack
		push(controller->redoStack, redoOperation);
		int duringUndo = 1;
		updateProfileController(controller, getProfileIdNumber(profile), getPlaceOfBirth(profile), getPsychologicalProfile(profile), getYearsOfRecordedService(profile), duringUndo);
		//destroyProfile(currentProfile);
	}
	else if (strcmp(getOperationType(operation), "delete") == 0)
	{
		Profile* profile = getProfileOperation(operation);
		// create the reverse operation for redo
		Operation* redoOperation = createOperation(profile, "add");
		// push it to the redo stack
		push(controller->redoStack, redoOperation);
		int duringUndo = 1;
		deleteProfileController(controller, getProfileIdNumber(profile), duringUndo);
	}

	destroyOperation(operation);

	return 0;
}

int redo(Controller* controller)
{
	// if the undoStack is empty, return an error
	if (isEmpty(controller->redoStack))
	{
		return -1;
	}

	Operation* operation = pop(controller->redoStack);

	if (strcmp(getOperationType(operation), "add") == 0)
	{
		Profile* profile = getProfileOperation(operation);

		// create the reverse operation for undo
		Operation* undoOperation = createOperation(profile, "delete");
		// push it to the undo stack
		push(controller->undoStack, undoOperation);

		int duringUndo = 1;
		addProfileController(controller, getProfileIdNumber(profile), getPlaceOfBirth(profile), getPsychologicalProfile(profile), getYearsOfRecordedService(profile), duringUndo);
	}
	else if (strcmp(getOperationType(operation), "update") == 0)
	{
		Profile* profile = getProfileOperation(operation); //the old profile

		// create the reverse operation for undo
		// we should memorize the currentProfile, which has the same IdNumber as the one from the undoStack operation
		Profile* currentProfile = getProfileByIdNumber(controller->repository, getProfileIdNumber(profile));
		Operation* undoOperation = createOperation(currentProfile, "update");
		// push it to the undo stack
		push(controller->undoStack, undoOperation);

		int duringUndo = 1;
		updateProfileController(controller, getProfileIdNumber(profile), getPlaceOfBirth(profile), getPsychologicalProfile(profile), getYearsOfRecordedService(profile), duringUndo);
	}
	else if (strcmp(getOperationType(operation), "delete") == 0)
	{
		Profile* profile = getProfileOperation(operation);

		// create the reverse operation for undo
		Operation* undoOperation = createOperation(profile, "add");
		// push it to the undo stack
		push(controller->undoStack, undoOperation);

		int duringUndo = 1;
		deleteProfileController(controller, getProfileIdNumber(profile), duringUndo);
	}

	destroyOperation(operation);

	return 0;
}

Repository* getAllProfilesController(Controller* controller)
{
	return getAllProfiles(controller->repository);
}

Repository* getFilteredProfilesAfterYearsOfServiceSortedAscendingController(Controller* controller, int maximumYearsOfService)
{
	Repository* repositoryFilteredAfterPsychologicalProfile = getFilteredProfilesAfterYearsOfService(controller->repository, maximumYearsOfService);
	repositoryFilteredAfterPsychologicalProfile->profiles = sortProfilesAscendingAfterPlaceOfBirth(repositoryFilteredAfterPsychologicalProfile->profiles);
	return repositoryFilteredAfterPsychologicalProfile;
}

Repository* getFilteredProfilesAfterPsychologicalProfileController(Controller* controller, char* psychologicalProfile)
{
	return getFilteredProfilesAfterPsychologicalProfile(controller->repository, psychologicalProfile);

}
