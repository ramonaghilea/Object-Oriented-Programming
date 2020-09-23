#pragma once
#include "Profile.h"

#define DYNAMIC_ARRAY_CAPACITY 10
typedef Profile* TElement;

typedef struct
{
	int capacity;
	int size;
	TElement* elements;
} DynamicArray;

/*
	Creates a DynamicArray
	input: - maxumum capacity (int)
	output: returns a pointer to a new DynamicArray
*/
DynamicArray* createDynamicArray(int capacity);
/*
	Destroys a DynamicArray
	input: pointer to a DynamicArray
	output: -
*/
void destroyDynamicArray(DynamicArray* DynamicArray);
/*
	Resizes a DynamicArray
	input: pointer to a DynamicArray
	output: - the DynamicArray doubles its capacity
*/
int resize(DynamicArray* dynamicArray);
/*
	Adds a TElement to the DynamicArray.
	input:
		- pointer to DynamicArray
		- TElement to be added
	output:
		- The element is added
*/
void addElement(DynamicArray* DynamicArray, TElement element);
/*
	Deletes a TElement from the DynamicArray.
	input:
		- pointer to DynamicArray
		- int position of the TElement to be deleted
	output:
		- The element is deleted
*/
void deleteElement(DynamicArray* DynamicArray, int positionElement);
/*
	Updates a TElement in the DynamicArray.
	input:
		- pointer to DynamicArray
		- int position of the TElement to be updated
		- the new TElement
	output:
		- The element is updated
*/
void updateElement(DynamicArray* DynamicArray, int positionElement, TElement element);

/*
	Gets a TElement by the position in the DynamicArray.
	input:
		- pointer to DynamicArray
		- int positionElement
	output:
		- returns the TElement on position positionElement
*/
TElement getElementByPosition(DynamicArray* dynamicArray, int positionElement);
/*
	Gets the size of the DynamicArray.
	input:
		- pointer to DynamicArray
	output:
		- returns an integer representing the size of the DynamicArray
*/
int getSize(DynamicArray* DynamicArray);
/*
	Gets the index(position) in the DynamicArray of a Profile by the ProfileIdNumber.
	input:
		- pointer to DynamicArray
		- int profileIdNumber
	output:
		- returns the index of the Profile with the specific profileIdNumber
*/
int getIndexProfileByProfileIdNumber(DynamicArray* dynamicArray, int profileIdNumber);

/*
	Compares the placeOfBirth of 2 profiles.
	input:
		- TElement 1
		- TElement 2
	output:
		- returns 0 if placeOfBirth(TElement1) < placeOfBirth(TElement2), 1 otherwise
*/
int comparationFunctionPLaceOfBIrth(TElement* element1, TElement* element2);
/*
	Sorts the elements of the DynamicArray ascending based on placeOfBirth. Calls comparationFunctionPLaceOfBIrth.
	input:
		- pointer to DynamicArray
	output:
		- returns a new DynamicArray with the elements sorted
*/
DynamicArray* sortProfilesAscendingAfterPlaceOfBirth(DynamicArray* dynamicArray);
