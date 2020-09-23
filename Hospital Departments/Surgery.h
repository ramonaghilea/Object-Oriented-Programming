#pragma once
#include "HospitalDepartment.h"

class Surgery: public HospitalDepartment
{
private:
	int numberOfPacients;
public:
	Surgery(std::string hospital, int numberOfDoctors, int numberOfPatients);
	bool isEfficient() override;
	std::string toString() override;
	std::string toStringFile() override;
};

