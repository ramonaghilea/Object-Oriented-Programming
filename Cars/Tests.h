#pragma once
#include "Car.h"
#include "Repository.h"
#include "Service.h"

void getNumberCarsForGivenManufacturer_ExistentManufacturer_ReturnsNumberOfCars();
void getNumberCarsForGivenManufacturer_InexistentManufacturer_ReturnsZero();

void runAllTests();

