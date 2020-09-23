#include "Service.h"
#include <algorithm>

std::vector<Car> Service::getAllCarsSortedByManufacturer()
{
	vector<Car> sortedCarsByManufacturer = this->repository.getAllCars();

	sort(sortedCarsByManufacturer.begin(), sortedCarsByManufacturer.end(), [](Car& car1, Car& car2)
		{
			return car1.getManufacturer() < car2.getManufacturer();
		});

	return sortedCarsByManufacturer;
}

int Service::getNumberCarsForGivenManufacturer(std::string manufacturer)
{
	int numberCars = 0;

	vector<Car> allCars = this->repository.getAllCars();

	for (auto car : allCars)
		if (car.getManufacturer() == manufacturer)
			numberCars++;

	return numberCars;
}
