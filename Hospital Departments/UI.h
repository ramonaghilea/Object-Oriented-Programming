#pragma once
#include "Controller.h"

class UI
{
private:
	Controller& controller;
public:
	UI(Controller& controller) : controller(controller) {};
	void start();

	void addDepartment(std::string inputParameters);
	void listDepartments();
	void listEfficientDepartments();
};

