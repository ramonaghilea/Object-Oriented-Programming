#include "Operation.h"
#include <stdlib.h>
#include <string.h>

Operation* createOperation(Profile* profile, char* operationType)
{
	Operation* operation = (Operation*)malloc(sizeof(Operation));
	operation->profile = copyProfile(profile);

	if (operationType != NULL)
	{
		operation->operationType = (char*)malloc(sizeof(char) * (strlen(operationType) + 1));
		strcpy(operation->operationType, operationType);
	}
	else
		operation->operationType = NULL;

	return operation;
}

void destroyOperation(Operation* operation)
{
	if (operation == NULL)
		return;

	destroyProfile(operation->profile);
	free(operation->operationType);
	free(operation);
}
//
//Operation* copyOperation(Operation* operation)
//{
//	if (operation == NULL)
//		return NULL;
//
//	Operation* copyOperation = createOperation(getProfileOperation(operation), getOperationType(operation));
//	return copyOperation;
//}

char* getOperationType(Operation* operation)
{
	return operation->operationType;
}

Profile* getProfileOperation(Operation* operation)
{
	return operation->profile;
}
