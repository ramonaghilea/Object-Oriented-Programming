#pragma once
#include <vector>
#include "Car.h"

using namespace std;

class Repository
{
private:
	string filename;

public:
	Repository(std::string filename);
	vector<Car> getAllCars();

private:
	vector<Car> loadData();
};

