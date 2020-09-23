#include "Tests.h"
#include <assert.h>

void getNumberCarsForGivenManufacturer_ExistentManufacturer_ReturnsNumberOfCars()
{
	Repository repository("testfile.txt");
	Service service(repository);

	assert(service.getNumberCarsForGivenManufacturer("Mercedes-Benz") == 2);
}

void getNumberCarsForGivenManufacturer_InexistentManufacturer_ReturnsZero()
{
	Repository repository("testfile.txt");
	Service service(repository);

	assert(service.getNumberCarsForGivenManufacturer("Skoda") == 0);
}

void runAllTests()
{
	getNumberCarsForGivenManufacturer_ExistentManufacturer_ReturnsNumberOfCars();
	getNumberCarsForGivenManufacturer_InexistentManufacturer_ReturnsZero();
}
