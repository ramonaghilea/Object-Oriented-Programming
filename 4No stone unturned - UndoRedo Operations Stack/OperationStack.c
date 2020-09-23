#include "OperationStack.h"
#include <stdlib.h>
#include <string.h>

OperationsStack* createStack()
{
	OperationsStack* operationStack = (OperationsStack*)malloc(sizeof(OperationsStack));
	operationStack->operations = createDynamicArrayOperations(DYNAMIC_ARRAY_CAPACITY);

	return operationStack;
}

void destroyStack(OperationsStack* operationStack)
{
	if (operationStack == NULL)
		return;

	destroyDynamicArrayOperations(operationStack->operations);
	free(operationStack);
}

void push(OperationsStack* operationStack, Operation* operation)
{
	if (operationStack == NULL || operation == NULL)
		return;
	addElementDynamicArrayOperations(operationStack->operations, operation);
}

Operation* pop(OperationsStack* operationStack)
{
	if(isEmpty(operationStack))
		return NULL;

	Operation* lastElementFromDynamicArray = getElementByPositionDynamicArrayOperations(operationStack->operations, getSizeDynamicArrayOperations(operationStack->operations) - 1);
	deleteElementDynamicArrayOperations(operationStack->operations, getSizeDynamicArrayOperations(operationStack->operations) - 1);

	return lastElementFromDynamicArray;
}

int isEmpty(OperationsStack* operationStack)
{
	return (getSizeDynamicArrayOperations(operationStack->operations) == 0);
}

int isFull(OperationsStack* operationStack)
{
	return (getSizeDynamicArrayOperations(operationStack->operations) == MAXIMUM_CAPACITY_OPERATION_STACK);
}

int getSizeOperationStack(OperationsStack* operationStack)
{
	return getSizeDynamicArrayOperations(operationStack->operations);
}

void clearStack(OperationsStack* operationStack)
{
	Operation* operation = (Operation*)malloc(sizeof(Operation));
	while (!isEmpty(operationStack)) {
		operation = pop(operationStack);
	}
	free(operation);
}