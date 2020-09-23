#include "User.h"

User::User(std::string uniqueUserName, std::string name)
{
	this->uniqueUserName = uniqueUserName;
	this->name = name;
}

std::string User::getUniqueUserName()
{
	return this->uniqueUserName;
}

std::string User::getName()
{
	return this->name;
}
