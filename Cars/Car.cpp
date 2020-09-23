#include "Car.h"

Car::Car()
{
}

Car::Car(std::string manufacturer, std::string model, int year, std::string colour)
{
	this->manufacturer = manufacturer;
	this->model = model;
	this->year = year;
	this->colour = colour;
}

std::string Car::getColour() const
{
	return this->colour;
}

std::string Car::getManufacturer() const
{
	return this->manufacturer;
}

std::string Car::getModel() const
{
	return this->model;
}

int Car::getYear() const
{
	return this->year;
}

std::string Car::asString()
{
	return this->getManufacturer() + " " + this->getModel();
}

std::vector<std::string> tokenizeStringCar(std::string carAsString, char* delimiter)
{
	std::vector<std::string> resultVectorStringCar{};
	int lengthDelimiter = 3;
	std::string parameter;

	if (carAsString.size() == 0)
		return resultVectorStringCar;

	while (carAsString.find(delimiter) >= 0 && carAsString.find(delimiter) < carAsString.size())
	{
		parameter = carAsString.substr(0, carAsString.find(delimiter));
		resultVectorStringCar.push_back(parameter);
		carAsString = carAsString.erase(0, carAsString.find(delimiter) + lengthDelimiter);
	}
	parameter = carAsString;
	resultVectorStringCar.push_back(parameter);

	return resultVectorStringCar;
}

std::istream& operator>>(std::istream& inputStream, Car& car)
{
	std::string inputLine;
	getline(inputStream, inputLine);
	char* delimiter = " | ";

	std::vector<std::string> resultVectorStringCarParameters = tokenizeStringCar(inputLine, delimiter);

	if (resultVectorStringCarParameters.size() == 0)
		return inputStream;

	// the Car has 4 parameters
	std::string manufacturer, model, colour;
	int year;

	manufacturer = resultVectorStringCarParameters[0];
	model = resultVectorStringCarParameters[1];
	year = atoi(resultVectorStringCarParameters[2].c_str());
	colour = resultVectorStringCarParameters[3];

	// assign the parameters to the car
	car.manufacturer = manufacturer;
	car.model = model;
	car.year = year;
	car.colour = colour;

	return inputStream;
}

std::ostream& operator<<(std::ostream& outputStream, Car& car)
{
	std::string carAsStringFileFormat = car.asString() + "\n";

	outputStream << carAsStringFileFormat;

	return outputStream;
}
