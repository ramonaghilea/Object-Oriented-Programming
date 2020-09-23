#include "Controller.h"

#include <iostream>
#include <fstream>

using namespace std;

std::string Controller::getPath()
{
	return this->filename;
}

void Controller::addDepartment(std::string hospital, std::string type, std::string inputParameters)
{
	if (type == "Surgery")
	{
		string commaDelimiter = ",";
		int lengthDelimiters = 2;

		string numberOfDoctors, numberOfPatients;
		int numberOfDoctorsInt, numberOfPatientsInt;

		numberOfDoctors = inputParameters.substr(0, inputParameters.find(commaDelimiter));
		inputParameters = inputParameters.erase(0, inputParameters.find(commaDelimiter) + lengthDelimiters);
		numberOfDoctorsInt = atoi(numberOfDoctors.c_str());

		numberOfPatients = inputParameters;
		numberOfPatientsInt = atoi(numberOfPatients.c_str());

		// cout << hospital << " " << type << " " << numberOfDoctors << " " << numberOfPatients << "\n";

		Surgery* newSurgery = new Surgery(hospital, numberOfDoctorsInt, numberOfPatientsInt);
		this->repository.addDepartment(newSurgery);
	}
	else
	{
		string commaDelimiter = ",";
		int lengthDelimiters = 2;

		string numberOfDoctors, numberOfMothers, numberOfBabies, average;
		int numberOfDoctorsInt, numberOfMothersInt, numberOfBabiesInt;
		double averageDouble;

		numberOfDoctors = inputParameters.substr(0, inputParameters.find(commaDelimiter));
		inputParameters = inputParameters.erase(0, inputParameters.find(commaDelimiter) + lengthDelimiters);
		numberOfDoctorsInt = atoi(numberOfDoctors.c_str());
		numberOfMothers = inputParameters.substr(0, inputParameters.find(commaDelimiter));
		inputParameters = inputParameters.erase(0, inputParameters.find(commaDelimiter) + lengthDelimiters);
		numberOfMothersInt = atoi(numberOfMothers.c_str());
		numberOfBabies = inputParameters.substr(0, inputParameters.find(commaDelimiter));
		inputParameters = inputParameters.erase(0, inputParameters.find(commaDelimiter) + lengthDelimiters);
		numberOfBabiesInt = atoi(numberOfBabies.c_str());
		average = inputParameters;
		averageDouble = atof(average.c_str());
		cout << to_string(averageDouble);

		NeonatalUnit* newSurgery = new NeonatalUnit(hospital, numberOfDoctorsInt, numberOfMothersInt, numberOfBabiesInt, averageDouble);
		this->repository.addDepartment(newSurgery);
	}
}

std::vector<HospitalDepartment*> Controller::getAllDepartments()
{
	return this->repository.getAll();
}

std::vector<HospitalDepartment*> Controller::getAllEfficientDepartments()
{
	std::vector<HospitalDepartment*> HospitalDepartments = this->repository.getAll();
	std::vector<HospitalDepartment*> HospitalDepartmentsEfficient{};
	for (auto HospitalDepartment : HospitalDepartments)
	{
		if (HospitalDepartment->isEfficient())
			HospitalDepartmentsEfficient.push_back(HospitalDepartment);
	}

	return HospitalDepartmentsEfficient;
}

void Controller::writeToFile(std::string filename)
{
	std::vector<HospitalDepartment*> HospitalDepartments = this->repository.getAll();
	ofstream outputStream;
	outputStream.open(filename);

	for (auto department : HospitalDepartments)
		outputStream << department->toStringFile() << '\n';

	outputStream.close();
}

void Controller::setPath(std::string filename)
{
	this->filename = filename;
}
