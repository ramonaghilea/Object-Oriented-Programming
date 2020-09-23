#include "Repository.h"
#include <iostream>
#include <fstream>

Repository::Repository(std::string filename)
{
	this->filename = filename;
}

vector<Car> Repository::getAllCars()
{
	vector<Car> allCars = this->loadData();
	return allCars;
}

vector<Car> Repository::loadData()
{
	ifstream inputStream;
	inputStream.open(this->filename);

	vector<Car> cars{};
	Car car{};

	while (inputStream >> car) // read while the boolean value of inputStream(ifstream) is true
	{
		cars.push_back(car);
	}

	inputStream.close();
	return cars;
}
