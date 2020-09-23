#include "Controller.h"
#include <stdlib.h>
#include <string.h>

Controller* createController(Repository* repository, DynamicArray* undoStack, DynamicArray* redoStack)
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
	destroyDynamicArray(controller->undoStack);
	destroyDynamicArray(controller->redoStack);

	free(controller);
}

int addProfileController(Controller* controller, int profileIdNumber, char* placeOfBirth, char* psychologicalProfile, int yearsOfRecordedService)
{
	int resultOfOperation;

	// make a copy of the current list of profiles in the repository
	DynamicArray* currentListProfiles = copyDynamicArray(getAllProfilesAsDynamicArray(controller->repository));

	Profile* newProfile = createProfile(profileIdNumber, placeOfBirth, psychologicalProfile, yearsOfRecordedService);

	resultOfOperation = addProfileRepository(controller->repository, newProfile);
	if (resultOfOperation == 0) //the operation was done successfully, register the current list of profiles
	{
		addElement(controller->undoStack, currentListProfiles);

		// clear the redoStack because a redo can only be perfomed after an undo
		clearDynamicArray(controller->redoStack);
	}
	else
	{
		// if the operation was not succesful, destroy the currentListProfiles(it is the same in the repo)
		destroyDynamicArray(currentListProfiles);
	}

	return resultOfOperation;
}

int updateProfileController(Controller* controller, int profileIdNumber, char* newPlaceOfBirth, char* newPsychologicalProfile, int newYearsOfRecordedService)
{
	int resultOfOperation;

	// make a copy of the current list of profiles in the repository
	DynamicArray* currentListProfiles = copyDynamicArray(getAllProfilesAsDynamicArray(controller->repository));

	Profile* newProfile = createProfile(profileIdNumber, newPlaceOfBirth, newPsychologicalProfile, newYearsOfRecordedService);

	Profile* oldProfile = getProfileByIdNumber(controller->repository, getProfileIdNumber(newProfile));

	resultOfOperation = updateProfileRepository(controller->repository, newProfile);

	if (resultOfOperation == 0) //the operation was done successfully and we are not durin undo, register the operation
	{
		addElement(controller->undoStack, currentListProfiles);

		// the operation was successfull, destroy the oldProfile, because the dynamicArray is not longer responsible with
		// destroynig it
		destroyProfile(oldProfile); /////CHANGE

		// clear the redoStack because a redo can only be perfomed after an undo
		clearDynamicArray(controller->redoStack);
	}
	else
	{
		// the operation was not successfull, destroy the newProfile, because we could not add it, but it was created
		destroyProfile(newProfile);
		// if the operation was not succesful, destroy the currentListProfiles(it is the same in the repo)
		destroyDynamicArray(currentListProfiles);
	}
		//destroyProfile(oldProfile); /////CHANGE

	return resultOfOperation;
}

int deleteProfileController(Controller* controller, int profileIdNumber)
{
	int resultOfOperation;

	// make a copy of the current list of profiles in the repository
	DynamicArray* currentListProfiles = copyDynamicArray(getAllProfilesAsDynamicArray(controller->repository));

	Profile* newProfile = getProfileByIdNumber(controller->repository, profileIdNumber);

	resultOfOperation = deleteProfileRepository(controller->repository, profileIdNumber);
	if (resultOfOperation == 0) //the operation was done successfully, register the operation
	{
		addElement(controller->undoStack, currentListProfiles);

		// the operation was successfull, destroy the Profile, because the dynamicArray is not longer responsible with
		// destroynig it, as it was deleted from the array
		destroyProfile(newProfile); /////CHANGE

		// clear the redoStack because a redo can only be perfomed after an undo
		clearDynamicArray(controller->redoStack);
	}
	else
	{
		// if the operation was not succesful, destroy the currentListProfiles(it is the same in the repo)
		destroyDynamicArray(currentListProfiles);
	}

	return resultOfOperation;
}

int getNumberProfilesController(Controller* controller)
{
	return getNumberProfiles(controller->repository);
}

int undo(Controller* controller)
{
	// if the undoStack is empty, return an error
	if (getSize(controller->undoStack) == 0)
	{
		return -1;
	}

	// get the last element from the undoStack (the last list)
	DynamicArray* previousListProfiles = getElementByPosition(controller->undoStack, getSize(controller->undoStack) - 1);
	// delete it from the undoStack
	deleteElement(controller->undoStack, getSize(controller->undoStack) - 1);

	// store the a copy of the current list of profiles in the redoStack
	DynamicArray* currentListProfiles = copyDynamicArray(getAllProfilesAsDynamicArray(controller->repository));
	addElement(controller->redoStack, currentListProfiles);

	// replace the current dynamicArray from repository with the previous one
	updateRepositoryNewDynamicArray(controller->repository, previousListProfiles);

	return 0;
}

int redo(Controller* controller)
{
	// if the redoStack is empty, return an error
	if (getSize(controller->redoStack) == 0)
	{
		return -1;
	}

	// get the last element from the undoStack (the last list)
	DynamicArray* previousListProfiles = getElementByPosition(controller->redoStack, getSize(controller->redoStack) - 1);
	// delete it from the undoStack
	deleteElement(controller->redoStack, getSize(controller->redoStack) - 1);

	// store the a copy of the current list of profiles in the undoStack
	DynamicArray* currentListProfiles = copyDynamicArray(getAllProfilesAsDynamicArray(controller->repository));
	addElement(controller->undoStack, currentListProfiles);

	// replace the current dynamicArray from repository with the previous one
	updateRepositoryNewDynamicArray(controller->repository, previousListProfiles);

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
