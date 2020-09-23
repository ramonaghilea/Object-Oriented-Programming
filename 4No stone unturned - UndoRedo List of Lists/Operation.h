#pragma once
#include "Profile.h"

typedef struct
{
	Profile* profile;
	char* operationType;
} Operation;

/*
	Creates an Operation
	input:
		- Profile* profile
		- char* operationType
	output: returns a pointer to a new Operation
*/
Operation* createOperation(Profile* profile, char* operationType);
/*
	Destroys an Operation
	input: pointer to an Operation
	output: -
*/
void destroyOperation(Operation* operation);
/*
	Gets the OperationType.
	input:
		- pointer to Operation
	output:
		- returns a char* representing the type of the operation
*/
char* getOperationType(Operation* operation);
/*
	Gets the OperationProfile
	input:
		- pointer to Operation
	output:
		- returns a Profile* representing the profile of the operation
*/
Profile* getProfileOperation(Operation* operation);