#pragma once
#include <exception>
#include <string>

class DatabaseException : public std::exception
{
private:
	std::string exceptionMessage;

public:
	DatabaseException(const std::string& exceptionMessage);
	const char* what() const noexcept override;
};

class MyListException : public std::exception
{
private:
	std::string exceptionMessage;

public:
	MyListException(const std::string& exceptionMessage);
	const char* what() const noexcept override;
};

class ValidationException : public std::exception
{
private:
	std::string exceptionMessage;

public:
	ValidationException(const std::string& exceptionMessage);
	const char* what() const noexcept override;
};