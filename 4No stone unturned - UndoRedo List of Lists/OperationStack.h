#pragma once
#include "Operation.h"
#include "DynamicArrayOperations.h"

#define MAXIMUM_CAPACITY_OPERATION_STACK 100

typedef struct
{
	DynamicArrayOperations* operations;

} OperationsStack;

/*
	Creates an OperationsStack
	input: -
	output: returns a pointer to a new OperationsStack
*/
OperationsStack* createStack();
/*
	Destroys an OperationStack
	input: pointer to an OperationsStack
	output: -
*/
void destroyStack(OperationsStack* operationStack);
/*
	Pushes an operation on the stack.
	input:
		- pointer to OperationsStack
		- pointer to the Operation to be pushed
	output:
		- 
*/
void push(OperationsStack* operationStack, Operation* operation);
/*
	Pops an operation from the stack.
	input:
		- pointer to OperationsStack
	output:
		- returns pointer to the Operation to be pushed
*/
Operation* pop(OperationsStack* operationStack);
/*
	Checks if the stack is empty.
	input:
		- pointer to OperationsStack
	output:
		- returns 1 if it is empty, 0 otherwise
*/
int isEmpty(OperationsStack* operationStack);
/*
	Checks if the stack is full.
	input:
		- pointer to OperationsStack
	output:
		- returns 1 if it is full, 0 otherwise
*/
int isFull(OperationsStack* operationStack);
/*
	Gets the size of the stack.
	input:
		- pointer to OperationsStack
	output:
		- returns an int representing the size of the stack
*/
int getSizeOperationStack(OperationsStack* operationStack);
/*
	Clears(empties) the stack.
	input:
		- pointer to OperationsStack
	output:
		-
*/
void clearStack(OperationsStack* operationStack);

