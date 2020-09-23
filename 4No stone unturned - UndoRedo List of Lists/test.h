#pragma once
#include "Profile.h"
#include "Repository.h"
#include "Controller.h"
#include "DynamicArray.h"
#include "Operation.h"
#include "OperationStack.h"

typedef void* TElement;
typedef void (*DestroyElementFunctionType)(void*);


void getProfileIdNumber_GivenProfile_ReturnProfileIdNumber();
void getPlaceofBirth_GivenProfile_ReturnPlaceOfBirth();
void getPsychologicalProfile_GivenProfile_ReturnPsychologicalProfile();
void getYearsOfRecordedService_GivenProfile_ReturnYearsOfRecordedService();
void copyProfile_GivenProfile_ReturnsCopyOfProfile();

void addElement_ValidObject_AddsToArray();
void deleteElement_ValidPositionOfObject_DeletesFromArray();
void getElement_ValidPositionOfObject_ReturnsObject();
void updateElement_ValidPositionOfObjectValidObject_UpdatesInArray();
void getIndexProfileByProfileIdNumber_GivenProfileIdNumber_ReturnIndexProfile();

void addProfileRepository_ValidProfile_AddsToRepository();
void addProfileRepository_DuplicateId_ReturnsError();
void updateProfileRepository_ValidProfile_UpdatesInRepository();
void updateProfileRepository_NonexistentId_ReturnsError();
void deleteProfileRepository_ValidProfile_DeletesFromRepository();
void deleteProfileRepository_NonexistentId_ReturnsError();

void addProfileController_ValidInput_AddsToController();
void addProfileController_DuplicateId_ReturnsError();
void updateProfileController_ValidProfile_UpdatesInController();
void updateProfileController_NonexistentId_ReturnsError();
void deleteProfileController_ValidProfile_DeletesFromController();
void deleteProfileController_NonexistentId_ReturnsError();
void undo_ValidUndo_UndoesTheLastOperation();
void redo_ValidRedo_RedoesTheLastOperation();

void getOperationType_ValidObject_ReturnOperationType();
void getProfileOperation_ValidObject_ReturnProfileOfOperation();

void push_ValidOperation_PushesOperationOnTheStack();
void pop_OperationStack_PopsOperationFromTheStack();
void isEmpty_OperationStack_ReturnsTrue();

void addElementGeneric_GenericDynamicArray_AddsToArray();

void testProfile();
void testDynamicArray();
void testRepository();
void testController();
void testOperation();
void testOperationStack();

void testAll();
