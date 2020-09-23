#pragma once
#include "HospitalDepartment.h"
#include <vector>

class Repository
{
private:
	std::vector<HospitalDepartment*> departments;
public:
	void setPath(std::string filename);
	void addDepartment(HospitalDepartment* departmentToAdd);
	std::vector<HospitalDepartment*> getAll();
	~Repository();
};
