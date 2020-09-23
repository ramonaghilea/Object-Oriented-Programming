#pragma once
#include "Operation.h"

#define DYNAMIC_ARRAY_CAPACITY 10

typedef struct
{
	int capacity;
	int size;
	Operation** elements;
} DynamicArrayOperations;

/*
	Creates a DynamicArray for Operations
	input: - maxumum capacity (int)
	output: returns a pointer to a new DynamicArrayOperations
*/
DynamicArrayOperations* createDynamicArrayOperations(int capacity);
/*
	Destroys a DynamicArrayOperations
	input: pointer to a DynamicArrayOperations
	output: -
*/
void destroyDynamicArrayOperations(DynamicArrayOperations* DynamicArrayOperations);
/*
	Resizes a DynamicArrayOperations
	input: pointer to a DynamicArrayOperations
	output: - the DynamicArrayOperations doubles its capacity
*/
int resizeDynamicArrayOperations(DynamicArrayOperations* DynamicArrayOperations);
/*
	Adds an Operation to the DynamicArrayOperations.
	input:
		- pointer to DynamicArrayOperations
		- pointer to Operation to be added
	output:
		- The Operation is added
*/
void addElementDynamicArrayOperations(DynamicArrayOperations* DynamicArrayOperations, Operation* element);
/*
	Deletes an Operation from the DynamicArray.
	input:
		- pointer to DynamicArrayOperations
		- int position of the Operation to be deleted
	output:
		- The Operation is deleted
*/
void deleteElementDynamicArrayOperations(DynamicArrayOperations* DynamicArrayOperations, int positionOperation);

/*
	Gets an Operation by the position in the DynamicArrayOperations.
	input:
		- pointer to DynamicArrayOperations
		- int positionOperation
	output:
		- returns the Operation* on position positionElement
*/
Operation* getElementByPositionDynamicArrayOperations(DynamicArrayOperations* DynamicArrayOperations, int positionOperation);
/*
	Gets the size of the DynamicArrayOperations.
	input:
		- pointer to DynamicArrayOperations
	output:
		- returns an integer representing the size of the DynamicArrayOperations
*/
int getSizeDynamicArrayOperations(DynamicArrayOperations* DynamicArrayOperations);
