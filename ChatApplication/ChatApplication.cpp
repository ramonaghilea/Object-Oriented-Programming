#include "ChatApplication.h"

using namespace std;

ChatApplication::ChatApplication(ChatSession& chatSession, User user, QWidget *parent)
    : chatSession(chatSession), user(user), QMainWindow(parent)
{
    ui.setupUi(this);
    this->connectSignalsAndSlots();
}

void ChatApplication::connectSignalsAndSlots()
{
    QObject::connect(this->ui.sendButton, &QPushButton::clicked, this, &ChatApplication::sendMessage);
}

void ChatApplication::update()
{
    this->populateList();
}

void ChatApplication::populateList()
{
    this->ui.messagesListWidget->clear();

    std::vector<std::pair<User, Message>> userMessages = this->chatSession.getMessages();
    for (auto message : userMessages)
    {
        std::string time;
        time += to_string(message.second.getTimestamp().tm_hour) + ":";
        std::string minutes = to_string(message.second.getTimestamp().tm_min);
        if (minutes.size() == 1)
            minutes.insert(0, "0");
        time += minutes;

        this->ui.messagesListWidget->addItem(QString::fromStdString(time + "\n" + message.first.getName() + ": " + message.second.getMessage()));
    }
}

void ChatApplication::sendMessage()
{
    std::string message = this->ui.newMessageLineEdit->text().toStdString();

    time_t now = time(0);
    tm *currentTime = localtime(&now);

    Message newMessage{ *currentTime, message };
    this->chatSession.addMessage(this->user, newMessage);
    this->ui.newMessageLineEdit->clear();
}
