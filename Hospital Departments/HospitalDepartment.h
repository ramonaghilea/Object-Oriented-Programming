#pragma once
#include <string>

class HospitalDepartment
{
protected:
	std::string hospitalName;
	int numberOfDoctors;

public:
	virtual bool isEfficient() = 0;
	virtual std::string toString();
	virtual std::string toStringFile();
	virtual ~HospitalDepartment() {};
};

