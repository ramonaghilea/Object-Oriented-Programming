#include "DistressCall.h"
#include "MyListWidget.h"
#include <QtWidgets/QApplication>
#include "Evidence.h"
#include "InMemoryRepository.h"
#include "FileRepository.h"
#include "CSVFileRepository.h"
#include "HTMLFileRepository.h"
#include "Service.h"
#include "PictureDelegate.h"
#include <crtdbg.h>
#include <iostream>
#include <fstream>
#include <memory>

using namespace std;

std::vector<std::string> readConfigurationFile()
{
	ifstream inputStream;
	inputStream.open("configurationFile.txt");

	vector<std::string> repositoryType{};
	std::string inputLine;

	while (inputStream >> inputLine) // read while the boolean value of inputStream(ifstream) is true
	{
		repositoryType.push_back(inputLine);
	}

	inputStream.close();
	return repositoryType;
}
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

	// initialize the repositories
	int databaseRepositoryType = 0, myListRepositoryType = 1;
	std::vector<std::string> repositoryType = readConfigurationFile();

	unique_ptr<Repository> databaseRepository = nullptr;
	//unique_ptr<InMemoryRepository> databaseInMemoryRepository = make_unique<InMemoryRepository>();
	unique_ptr<Repository> myListRepository = nullptr;

	if (repositoryType[databaseRepositoryType] == "InMemory")
		databaseRepository = make_unique<InMemoryRepository>();
	else if(repositoryType[databaseRepositoryType] == "CSVFileRepository")
		databaseRepository = make_unique<CSVFileRepository>("");
	else if (repositoryType[databaseRepositoryType] == "HTMLFileRepository")
		databaseRepository = make_unique<HTMLFileRepository>("");
	else
	{
		databaseRepository = make_unique<FileRepository>("");
	}

	if (repositoryType[myListRepositoryType] == "InMemory")
		myListRepository = make_unique<InMemoryRepository>();
	else if (repositoryType[myListRepositoryType] == "CSVFileRepository")
		myListRepository = make_unique<CSVFileRepository>("");
	else if (repositoryType[myListRepositoryType] == "HTMLFileRepository")
		myListRepository = make_unique<HTMLFileRepository>("");
	else
	{
		myListRepository = make_unique<FileRepository>("");
	}

	Service service(databaseRepository.get(), myListRepository.get());

	// create the model and the second window
	MyListTableModel* tableModel = new MyListTableModel{ myListRepository.get() };
	PictureDelegate* pictureDelegate = new PictureDelegate{ myListRepository.get() };
	MyListWidget* myList = new MyListWidget{ tableModel, pictureDelegate };
	myList->setWindowTitle("My List");
	//myList.show();

	// register the second window as observer
	service.registerObserver(myList);
	DistressCall gui{ service , myList};
	gui.show();

    return a.exec();
}
