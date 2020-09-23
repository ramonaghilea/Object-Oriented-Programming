#pragma once
#include "Repository.h"
#include "OperationStack.h"

typedef struct
{
	Repository* repository;
	OperationsStack* undoStack;
	OperationsStack* redoStack;
} Controller;

/*
	Creates a Controller;
	input: pointer to a Repository, undoStack, redoStack
	output: returns a pointer to a new Controller
*/
Controller* createController(Repository* repository, OperationsStack* undoStack, OperationsStack* redoStack);
/*
	Destroys a Controller;
	input: pointer to a Controller
	output: -
*/
void destroyController(Controller* controller);

/*
	Adds a profile to the Repository. Records the operation for undo. Calls addProfileRepository.
	input:
		- pointer to Controller
		- int profileIdNumber
		- char* placeOfBirth
		- char* psychologicalProfile
		- int yearsOfRecordedService
		- int duringUndo
	output:
		- returns an error if the Profile could not be added
*/
int addProfileController(Controller* controller, int profileIdNumber, char* placeOfBirth, char* psychologicalProfile, int yearsOfRecordedService, int duringUndo);
/*
	Updates a profile in the Repository. Records the operation for undo. Calls updateProfileRepository.
	input:
		- pointer to Controller
		- int profileIdNumber
		- char* placeOfBirth
		- char* psychologicalProfile
		- int yearsOfRecordedService
		- int duringUndo
	output:
		- returns an error if the Profile could not be updated
*/
int updateProfileController(Controller* controller, int profileIdNumber, char* newPlaceOfBirth, char* newPsychologicalProfile, int newYearsOfRecordedService, int duringUndo);
/*
	Deletes a profile from the Repository. Records the operation for undo. Calls deleteProfileRepository.
	input:
		- pointer to Controller
		- int profileIdNumber
		- int duringUndo
	output:
		- returns an error if the Profile could not be deleted
*/
int deleteProfileController(Controller* controller, int profileIdNumber, int duringUndo);
/*
	Undoes the last operation.
	input:
		- pointer to Controller
	output:
		- returns an error if it could not undo
*/
int undo(Controller* controller);
/*
	Redoes the last undo.
	input:
		- pointer to Controller
	output:
		- returns an error if it could not redo
*/
int redo(Controller* controller);

/*
	Gets the numberOfProfiles.
	input:
		- pointer to Controller
	output:
		- returns the numberOfProfiles
*/
int getNumberProfilesController(Controller* controller);
/*
	Gets all the profiles as a Repository.
	input:
		- pointer to Controller
	output:
		- returns a Repository with all the profiles
*/
Repository* getAllProfilesController(Controller* controller);
/*
	Gets all the profiles that have YearsOfRecordedService < maximumYearsOfService in ascending order as a Repository.
	input:
		- pointer to Controller
		- int maximumYearsOfService
	output:
		- returns a Repository with the profiles that match the criteria
*/
Repository* getFilteredProfilesAfterYearsOfServiceSortedAscendingController(Controller* controller, int maximumYearsOfService);
/*
	Gets all the profiles that have the psychologicalProfile the same as parameter PsychologicalProfile as a Repository.
	input:
		- pointer to Controller
		- char* psychologicalProfile
	output:
		- returns a Repository with the profiles that match the criteria
*/
Repository* getFilteredProfilesAfterPsychologicalProfileController(Controller* controller, char* psychologicalProfile);