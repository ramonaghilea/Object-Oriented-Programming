#include "ChatApplication.h"
#include <QtWidgets/QApplication>
#include "ChatSession.h"
#include "Subject.h"
#include "User.h"
#include "Observer.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    ChatSession chatSession;

    User userAmelia = User{ "1234", "Amelia" };
    User userDan = User{ "875", "Dan" };
    User userEmily = User{ "800", "Emily" };

    ChatApplication chatWindow1{ chatSession, userAmelia };
    chatWindow1.setWindowTitle("Amelia");
    ChatApplication chatWindow2{ chatSession, userDan };
    chatWindow2.setWindowTitle("Dan");
    ChatApplication chatWindow3{ chatSession, userEmily };
    chatWindow3.setWindowTitle("Emily");

    chatSession.registerObserver(&chatWindow1);
    chatSession.registerObserver(&chatWindow2);
    chatSession.registerObserver(&chatWindow3);

    chatWindow1.show();
    chatWindow2.show();
    chatWindow3.show();

    return a.exec();
}
