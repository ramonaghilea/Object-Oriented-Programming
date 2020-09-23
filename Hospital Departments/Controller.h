#pragma once
#include "HospitalDepartment.h"
#include "Surgery.h"
#include "NeonatalUnit.h"
#include "Repository.h"
#include <vector>

class Controller
{
private:
	Repository& repository;
	std::string filename{ "" };
public:
	Controller(Repository& repository) : repository(repository) {};
	std::string getPath();
	void setPath(std::string filename);
	void addDepartment(std::string hospital, std::string type, std::string inputParameters);
	std::vector<HospitalDepartment*> getAllDepartments();
	std::vector<HospitalDepartment*> getAllEfficientDepartments();
	void writeToFile(std::string filename);
};