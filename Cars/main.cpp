#include "TestWeek13.h"
#include <QtWidgets/QApplication>
#include "Repository.h"
#include "Service.h"
#include "Tests.h"

int main(int argc, char *argv[])
{
    runAllTests();

    QApplication a(argc, argv);
    Repository repository{ "cars.txt" };
    Service service{ repository };
    TestWeek13 gui{ service };

    gui.show();
    return a.exec();
}
