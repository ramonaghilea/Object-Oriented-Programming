#include "Surgery.h"
using namespace std;

Surgery::Surgery(std::string hospital, int numberOfDoctors, int numberOfPatients)
{
	this->hospitalName = hospital;
	this->numberOfDoctors = numberOfDoctors;
	this->numberOfPacients = numberOfPatients;
}

bool Surgery::isEfficient()
{
	if (this->numberOfDoctors == 0)
		return false;
	if (this->numberOfPacients / this->numberOfDoctors >= 2)
		return true;
	return false;
}

std::string Surgery::toString()
{
	return this->hospitalName + " Surgery " + to_string(this->numberOfDoctors) + " " + to_string(this->numberOfPacients);
}

std::string Surgery::toStringFile()
{
	if (this->isEfficient())
		return this->hospitalName + " Surgery " + to_string(this->numberOfDoctors) + " " + to_string(this->numberOfPacients) + " efficient";
	else
		return this->hospitalName + " Surgery " + to_string(this->numberOfDoctors) + " " + to_string(this->numberOfPacients) + " not efficient";
}
