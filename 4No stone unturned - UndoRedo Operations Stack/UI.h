#pragma once
#include "Controller.h"

typedef struct
{
	Controller* controller;
} UI;

/*
	Creates an UI;
	input: pointer to a Controller
	output: returns a pointer to a new UI
*/
UI* createUI(Controller* controller);
/*
	Destroys an UI.
	input: pointer to an UI
	outpt: -
*/
void destroyUI(UI* ui);

/*
	Adds a profile to the list. Calls addProfileController.
	input:
		- pointer to UI
		- inputParameters given by the user
	output:
		- returns an error if the Profile could not be added (prints "NO!")
*/
int addProfileUI(UI* ui, char* inputParameters);
/*
	Updates a profile from the list. Calls updateProfileController.
	input:
		- pointer to UI
		- inputParameters given by the user
	output:
		- returns an error if the Profile could not be updated (prints "NO!")
*/
int updateProfileUI(UI* ui, char* inputParameters);
/*
	Deletes a profile to the list. Calls addProfileController.
	input:
		- pointer to UI
		- inputParameters given by the user
	output:
		- returns an error if the Profile could not be deleted (prints "NO!")
*/
int deleteProfileUI(UI* ui, char* inputParameters);
/*
	Undoes the last operation. Calls undo from Controller.
	input:
		- pointer to UI
	output:
		- returns an error if it could not undo ("No more undoes.)
*/
int undoUI(UI* ui);
/*
	Redoes the last operation. Calls redo from Controller.
	input:
		- pointer to UI
	output:
		- returns an error if it could not redo ("No more redoes.)
*/
int redoUI(UI* ui);

/*
	Transforms a Profile to string.
	input:
		- pointer to a Profile
	output:
		- returns Profile as string
*/
char* getProfileAsString(Profile* profile);
/*
	Lists all profiles.
	input:
		- pointer to UI
	output:
		- prints all profiles
*/
void listProfilesUI(UI* ui);
/*
	Lists all profiles having the psychologicalProfile the input given by the user.
	input:
		- pointer to UI
		- inputParameter (psychologicalProfile)
	output:
		- prints all profiles with that specific psychologicalProfile
*/
void listPsychologicalProfilesUI(UI* ui, char* inputParameter);
/*
	Lists all profiles having maximumYearsOfService the input given by the user in ascending order.
	input:
		- pointer to UI
		- inputParameter (YearsOfService)
	output:
		- prints all profiles having maximumYearsOfService the input given by the user in ascending order
*/
void listMaximumYearsOfServiceUI(UI* ui, char* inputParameter);

/*
	Contains the main loop. Interprets the command and calls the other functions from UI.
	input:
		- pointer to UI
	output:
		- 
*/
void startUI(UI* ui);

