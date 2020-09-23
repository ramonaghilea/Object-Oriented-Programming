#pragma once
#include "Repository.h"
#include <vector>

class Service
{
private:
	Repository& repository;

public:
	Service(Repository& repository) : repository(repository) {};

	std::vector<Car> getAllCarsSortedByManufacturer();


	/*
	Computes the number of cars for a given manufacturer.
	input:
		- given manufacturer(std::string)
	output:
		- the number of cars for the given manufacurer (int)
	*/
	int getNumberCarsForGivenManufacturer(std::string manufacturer);

};

