#include "UI.h"
#include <iostream>

using namespace std;

void UI::start()
{
	string input{ "" };

	while (true)
	{
		string spaceDelimiter = " ", inputCommand, inputParameters;

		getline(cin, input);

		inputCommand = input.substr(0, input.find(spaceDelimiter));

		try
		{
			if (inputCommand == "exit")
			{
				return;
			}
			else if (inputCommand == "fileLocation")
			{
				inputParameters = input.erase(0, input.find(spaceDelimiter) + spaceDelimiter.length());
				this->controller.setPath(inputParameters);
			}
			else if (inputCommand == "add")
			{
				inputParameters = input.erase(0, input.find(spaceDelimiter) + spaceDelimiter.length());
				this->addDepartment(inputParameters);
			}
			else if (inputCommand == "list")
			{
				if (input == "list")
				{
					listDepartments();
				}
				else
				{
					listEfficientDepartments();
				}
			}
			else
			{
				cout << "Bad command. \n";
			}
		}
		catch (exception& exceptionCaught)
		{
			cout << exceptionCaught.what() << "\n";
		}
	}
}

void UI::addDepartment(std::string inputParameters)
{
	string commaDelimiter = ",";
	int lengthDelimiters = 2;

	string type, hospital;

	hospital = inputParameters.substr(0, inputParameters.find(commaDelimiter));
	inputParameters = inputParameters.erase(0, inputParameters.find(commaDelimiter) + lengthDelimiters);
	type = inputParameters.substr(0, inputParameters.find(commaDelimiter));
	inputParameters = inputParameters.erase(0, inputParameters.find(commaDelimiter) + lengthDelimiters);

	this->controller.addDepartment(hospital, type, inputParameters);
}

void UI::listDepartments()
{
	std::string filename = this->controller.getPath();

	if(this->controller.getPath() != "")
		this->controller.writeToFile(filename);
	else
	{
		std::vector<HospitalDepartment*> HospitalDepartments = this->controller.getAllDepartments();
		for (auto department : HospitalDepartments)
			std::cout << department->toString() << "\n";
	}
}

void UI::listEfficientDepartments()
{
	std::vector<HospitalDepartment*> HospitalDepartments = this->controller.getAllEfficientDepartments();
	for (auto department : HospitalDepartments)
		std::cout << department->toString() << "\n";
}
