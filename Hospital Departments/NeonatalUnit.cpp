#include "NeonatalUnit.h"

using namespace std;

NeonatalUnit::NeonatalUnit(std::string hospital, int numberOfDoctors, int numberOfMothers, int numberOfBabies, double averageGrade)
{
	this->hospitalName = hospital;
	this->numberOfDoctors = numberOfDoctors;
	this->numberOfMothers = numberOfMothers;
	this->numberOfNewborns = numberOfBabies;
	this->averageGrade = averageGrade;
}

bool NeonatalUnit::isEfficient()
{
	if (this->averageGrade > 8.5 && this->numberOfNewborns >= this->numberOfMothers)
		return true;
	return false;
}

std::string NeonatalUnit::toString()
{
	return this->hospitalName + " NeonatalUnit " + to_string(this->numberOfDoctors) + " " + to_string(this->numberOfMothers) + " " + to_string(this->numberOfNewborns) + " " + to_string(this->averageGrade);
}

std::string NeonatalUnit::toStringFile()
{
	if (this->isEfficient())
		return this->hospitalName + " NeonatalUnit " + to_string(this->numberOfDoctors) + " " + to_string(this->numberOfNewborns) + " " + to_string(this->averageGrade) + " efficient";
	else
		return this->hospitalName + " NeonatalUnit " + to_string(this->numberOfDoctors) + " " + to_string(this->numberOfNewborns) + " " + to_string(this->averageGrade) + " not efficient";
}
