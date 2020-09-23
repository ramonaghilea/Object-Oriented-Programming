#pragma once
#include "HospitalDepartment.h"

class NeonatalUnit: public HospitalDepartment
{
private:
	int numberOfMothers, numberOfNewborns;
	double averageGrade;
public:
	NeonatalUnit(std::string hospital, int numberOfDoctors, int numberOfMothers, int numberOfBabies, double averageGrade);
	bool isEfficient() override;
	std::string toString() override;
	std::string toStringFile() override;
};

