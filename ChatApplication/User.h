#pragma once
#include <string>

class User
{
private:
	std::string uniqueUserName;
	std::string name;

public:
	User(std::string uniqueUserName, std::string name);

	std::string getUniqueUserName();
	std::string getName();

};

