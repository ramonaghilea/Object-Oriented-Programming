#include "Exceptions.h"

DatabaseException::DatabaseException(const std::string& exceptionMessage)
{
	this->exceptionMessage = exceptionMessage;
}

const char* DatabaseException::what() const noexcept
{
	return this->exceptionMessage.c_str();
}

MyListException::MyListException(const std::string& exceptionMessage)
{
	this->exceptionMessage = exceptionMessage;
}

const char* MyListException::what() const noexcept
{
	return this->exceptionMessage.c_str();
}

ValidationException::ValidationException(const std::string& exceptionMessage)
{
	this->exceptionMessage = exceptionMessage;
}

const char* ValidationException::what() const noexcept
{
	return this->exceptionMessage.c_str();
}
