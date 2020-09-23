#pragma once
#include "Subject.h"
#include "User.h"
#include "Message.h"

class ChatSession: public Subject
{
private:
	std::vector<std::pair<User, Message>> userMessages{};

public:
	void addMessage(User user, Message message);
	std::vector<std::pair<User, Message>> getMessages();
};

