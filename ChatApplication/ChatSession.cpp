#include "ChatSession.h"

void ChatSession::addMessage(User user, Message message)
{
	std::pair<User, Message> newPair = std::make_pair(user, message);
	this->userMessages.push_back(newPair);

	this->notify();
}

std::vector<std::pair<User, Message>> ChatSession::getMessages()
{
	return this->userMessages;
}
