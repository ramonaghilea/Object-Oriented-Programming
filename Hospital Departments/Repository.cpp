#include "Repository.h"

void Repository::addDepartment(HospitalDepartment* departmentToAdd)
{
	this->departments.push_back(departmentToAdd);
}

std::vector<HospitalDepartment*> Repository::getAll()
{
	return this->departments;
}

Repository::~Repository()
{
	for (auto department : this->departments)
		delete department;
}
