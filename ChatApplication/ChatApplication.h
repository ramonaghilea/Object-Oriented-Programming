#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_ChatApplication.h"
#include "Observer.h"
#include "User.h"
#include "ChatSession.h"

class ChatApplication : public QMainWindow, public Observer
{
    Q_OBJECT

public:
    ChatApplication(ChatSession& chatSession, User user, QWidget *parent = Q_NULLPTR);

private:
    ChatSession& chatSession;
    User user;
    Ui::ChatApplicationClass ui;

public:
    void connectSignalsAndSlots();

    void update() override;
    void populateList();

    void sendMessage();
};
