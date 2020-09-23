#include "Message.h"

Message::Message(tm timestamp, std::string message)
{
	this->timestamp = timestamp;
	this->message = message;
}

tm Message::getTimestamp()
{
	return this->timestamp;
}

std::string Message::getMessage()
{
	return this->message;
}

void Message::setTimestamp(tm timestamp)
{
	this->timestamp = timestamp;
}

void Message::setMessage(std::string Message)
{
	this->message = message;
}
