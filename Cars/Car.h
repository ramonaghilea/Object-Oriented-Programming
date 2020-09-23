#pragma once
#include <string>
#include <vector>
#include <iostream>

class Car
{
private:
	std::string manufacturer, model, colour;
	int year;

public:
	Car();
	Car(std::string manufacturer, std::string model, int year, std::string colour);
	std::string getColour() const;
	std::string getManufacturer() const;
	std::string getModel() const;
	int getYear() const;

	std::string asString();

	friend std::vector<std::string> tokenizeStringCar(std::string carAsString, char* delimiter);
	friend std::istream& operator>>(std::istream& inputStream, Car& car);
	friend std::ostream& operator<<(std::ostream& outputStream, Car& car);
};

