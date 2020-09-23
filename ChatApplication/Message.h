#pragma once
#include <string>

class Message
{
private:
	tm timestamp;
	std::string message;
public:
	Message(tm timestamp, std::string message);

	tm getTimestamp();
	std::string getMessage();

	void setTimestamp(tm timestamp);
	void setMessage(std::string Message);
};

