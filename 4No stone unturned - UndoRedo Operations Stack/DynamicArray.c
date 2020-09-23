#include "DynamicArray.h"
#include <stdlib.h>
#include <string.h>

DynamicArray* createDynamicArray(int capacity)
{
	DynamicArray* dynamicArray = (DynamicArray*)malloc(sizeof(DynamicArray));
	if (dynamicArray == NULL)
		return NULL;

	dynamicArray->capacity = capacity;
	dynamicArray->size = 0;
	dynamicArray->elements = (TElement*)malloc(capacity * sizeof(TElement));
	if (dynamicArray->elements == NULL)
		return NULL;

	return dynamicArray;
}

void destroyDynamicArray(DynamicArray* dynamicArray)
{
	if (dynamicArray == NULL)
		return;
	// considering that the dynamic array takes responsibility of all the elements, it will have to deallocate the memory for these
	for (int indexElement = 0; indexElement < dynamicArray->size; indexElement++)
		destroyProfile(dynamicArray->elements[indexElement]);
	free(dynamicArray->elements);
	dynamicArray->elements = NULL;
	free(dynamicArray);
	dynamicArray = NULL;
}


int resize(DynamicArray* dynamicArray)
{
	if (dynamicArray == NULL)
		return -1;

	dynamicArray->capacity *= 2;

	//allocate new memory, copy the elements and deallocate the old memory
	TElement* newDynamicArray = (TElement*)malloc(dynamicArray->capacity * sizeof(TElement));
	if (newDynamicArray == NULL)
		return -1;
	for (int indexElement = 0; indexElement < dynamicArray->size; indexElement++)
		newDynamicArray[indexElement] = dynamicArray->elements[indexElement];
	free(dynamicArray->elements);
	dynamicArray->elements = newDynamicArray;

	return 0;
}

void addElement(DynamicArray* dynamicArray, TElement element)
{
	if (dynamicArray == NULL)
		return;
	if (dynamicArray->elements == NULL)
		return;

	// resize the array, if necessary
	if (dynamicArray->size == dynamicArray->capacity)
		resize(dynamicArray);

	dynamicArray->elements[dynamicArray->size] = element;
	dynamicArray->size++;
}

void deleteElement(DynamicArray* dynamicArray, int positionElement)
{
	if (dynamicArray == NULL)
		return;
	if (dynamicArray->elements == NULL)
		return;

	for (int indexElement = positionElement; indexElement < dynamicArray->size - 1; indexElement++)
	{
		dynamicArray->elements[indexElement] = dynamicArray->elements[indexElement + 1];
	}
	dynamicArray->size--;
}

void updateElement(DynamicArray* dynamicArray, int positionElement, TElement element)
{
	if (dynamicArray == NULL)
		return;
	if (dynamicArray->elements == NULL)
		return;
	dynamicArray->elements[positionElement] = element;

}
int getSize(DynamicArray* dynamicArray)
{
	if (dynamicArray == NULL)
		return -1;
	return dynamicArray->size;
}

TElement getElementByPosition(DynamicArray* dynamicArray, int positionElement)
{
	if (dynamicArray == NULL)
		return NULL;
	if (positionElement < 0 || positionElement >= dynamicArray->size)
		return NULL;
	return dynamicArray->elements[positionElement];
}

int getIndexProfileByProfileIdNumber(DynamicArray* dynamicArray, int profileIdNumber)
{
	if (dynamicArray->size == 0)
	{
		return -1;
	}

	for (int indexProfile = 0; indexProfile < dynamicArray->size; indexProfile++)
	{
		if (getProfileIdNumber(dynamicArray->elements[indexProfile]) == profileIdNumber)
		{
			return indexProfile;
		}
	}
	return -1;
}

int comparationFunctionPLaceOfBIrth(TElement* element1, TElement* element2)
{
	if (strcmp(getPlaceOfBirth(element1), getPlaceOfBirth(element2)) < 0)
	{
		//they are in alphabetical order
		return 0;
	}
	return 1;
}

DynamicArray* sortProfilesAscendingAfterPlaceOfBirth(DynamicArray* dynamicArray)
{
	Profile* profile;
	int indexProfile1, indexProfile2;
	for (indexProfile1 = 0; indexProfile1 < dynamicArray->size - 1; indexProfile1++)
	{
		for (indexProfile2 = indexProfile1 + 1; indexProfile2 < dynamicArray->size; indexProfile2++)
		{
			if (comparationFunctionPLaceOfBIrth(dynamicArray->elements[indexProfile1], dynamicArray->elements[indexProfile2]))
			{
				profile = dynamicArray->elements[indexProfile1];
				dynamicArray->elements[indexProfile1] = dynamicArray->elements[indexProfile2];
				dynamicArray->elements[indexProfile2] = profile;
			}
		}
	}
	return dynamicArray;
}