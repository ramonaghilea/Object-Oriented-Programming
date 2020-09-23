#include "DynamicArrayOperations.h"
#include <stdlib.h>
#include <string.h>

DynamicArrayOperations* createDynamicArrayOperations(int capacity)
{
	DynamicArrayOperations* dynamicArrayOperations = (DynamicArrayOperations*)malloc(sizeof(DynamicArrayOperations));
	if (dynamicArrayOperations == NULL)
		return NULL;

	dynamicArrayOperations->capacity = capacity;
	dynamicArrayOperations->size = 0;
	dynamicArrayOperations->elements = (Operation**)malloc(capacity * sizeof(Operation*));
	if (dynamicArrayOperations->elements == NULL)
		return NULL;

	return dynamicArrayOperations;
}

void destroyDynamicArrayOperations(DynamicArrayOperations* dynamicArrayOperations)
{
	if (dynamicArrayOperations == NULL)
		return;
	// considering that the dynamic array takes responsibility of all the elements, it will have to deallocate the memory for these
	for (int indexElement = 0; indexElement < dynamicArrayOperations->size; indexElement++)
		destroyOperation(dynamicArrayOperations->elements[indexElement]);
	free(dynamicArrayOperations->elements);
	dynamicArrayOperations->elements = NULL;
	free(dynamicArrayOperations);
	dynamicArrayOperations = NULL;
}


int resizeDynamicArrayOperations(DynamicArrayOperations* dynamicArrayOperations)
{
	if (dynamicArrayOperations == NULL)
		return -1;

	dynamicArrayOperations->capacity *= 2;

	//allocate new memory, copy the elements and deallocate the old memory
	Operation* newDynamicArrayOperations = (Operation**)malloc(dynamicArrayOperations->capacity * sizeof(Operation*));
	if (newDynamicArrayOperations == NULL)
		return -1;
	for (int indexElement = 0; indexElement < dynamicArrayOperations->size; indexElement++)
		newDynamicArrayOperations[indexElement] = *dynamicArrayOperations->elements[indexElement];
	free(dynamicArrayOperations->elements);
	dynamicArrayOperations->elements = newDynamicArrayOperations;

	return 0;
}

void addElementDynamicArrayOperations(DynamicArrayOperations* dynamicArrayOperations, Operation* element)
{
	if (dynamicArrayOperations == NULL)
		return;
	if (dynamicArrayOperations->elements == NULL)
		return;

	// resize the array, if necessary
	if (dynamicArrayOperations->size == dynamicArrayOperations->capacity)
		resize(dynamicArrayOperations);

	dynamicArrayOperations->elements[dynamicArrayOperations->size] = element;
	dynamicArrayOperations->size++;
}

void deleteElementDynamicArrayOperations(DynamicArrayOperations* dynamicArrayOperations, int positionOperation)
{
	if (dynamicArrayOperations == NULL)
		return;
	if (dynamicArrayOperations->elements == NULL)
		return;

	for (int indexElement = positionOperation; indexElement < dynamicArrayOperations->size - 1; indexElement++)
	{
		dynamicArrayOperations->elements[indexElement] = dynamicArrayOperations->elements[indexElement + 1];
	}
	dynamicArrayOperations->size--;
}

int getSizeDynamicArrayOperations(DynamicArrayOperations* dynamicArrayOperations)
{
	if (dynamicArrayOperations == NULL)
		return -1;
	return dynamicArrayOperations->size;
}

Operation* getElementByPositionDynamicArrayOperations(DynamicArrayOperations* dynamicArrayOperations, int positionOperation)
{
	if (dynamicArrayOperations == NULL)
		return NULL;
	if (positionOperation < 0 || positionOperation >= dynamicArrayOperations->size)
		return NULL;
	return dynamicArrayOperations->elements[positionOperation];
}
