#include "CSVFileRepository.h"
#include <iostream>
#include <fstream>

using namespace std;

CSVFileRepository::CSVFileRepository(const std::string& fileName)
{
	this->fileName = fileName;
}

void CSVFileRepository::addEvidenceFile(const EvidenceFile& evidenceFileToAdd)
{
	std::vector<EvidenceFile> myListEvidenceFiles = this->loadDataFromFile();

	// check if the EvidenceFile is not already added
	for (auto evidence : myListEvidenceFiles)
		if (evidence.getId() == evidenceFileToAdd.getId()) //the file already exists
			throw MyListException("The file already exists in myList.");

	myListEvidenceFiles.push_back(evidenceFileToAdd);

	this->storeDataToFile(myListEvidenceFiles);
}

void CSVFileRepository::deleteEvidenceFile(const std::string& evidenceFileToDeleteId)
{
	std::vector<EvidenceFile> myListEvidenceFiles = loadDataFromFile();

	for (int indexEvidenceFile = 0; indexEvidenceFile < myListEvidenceFiles.size(); indexEvidenceFile++)
		if (myListEvidenceFiles[indexEvidenceFile].getId() == evidenceFileToDeleteId) // if the evidence file is found, delete it
		{
			myListEvidenceFiles.erase(myListEvidenceFiles.begin() + indexEvidenceFile);
			break;
		}

	storeDataToFile(myListEvidenceFiles);
}

void CSVFileRepository::updateEvidenceFile(const EvidenceFile& evidenceFileToUpdate)
{
	std::vector<EvidenceFile> myListEvidenceFiles = loadDataFromFile();
	bool isEvidenceFileUpdated = false;

	for (int indexEvidenceFile = 0; indexEvidenceFile < myListEvidenceFiles.size(); indexEvidenceFile++)
		if (myListEvidenceFiles[indexEvidenceFile].getId() == evidenceFileToUpdate.getId()) // if the evidence file is found, update it it
		{
			myListEvidenceFiles[indexEvidenceFile] = evidenceFileToUpdate;
			break;
		}

	storeDataToFile(myListEvidenceFiles);
}

std::vector<EvidenceFile> CSVFileRepository::loadDataFromFile()
{
	ifstream inputStream;
	inputStream.open(this->fileName);

	vector<EvidenceFile> myListEvidenceFiles{};
	EvidenceFile evidenceFile;

	while (inputStream >> evidenceFile) // read while the boolean value of inputStream(ifstream) is true
	{
		ValidatorEvidenceFile::validateEvidenceFile(evidenceFile);
		myListEvidenceFiles.push_back(evidenceFile);
	}

	inputStream.close();
	return myListEvidenceFiles;
}

void CSVFileRepository::storeDataToFile(std::vector<EvidenceFile> evidenceFiles)
{
	ofstream outputStream;
	outputStream.open(this->fileName, ios::out);

	for (auto evidenceFile : evidenceFiles)
		outputStream << evidenceFile;

	outputStream.close();
}

void CSVFileRepository::openExternal()
{
	std::string myListFilePath = this->fileName;
	std::string command = "\"C:\\Program Files\\Microsoft Office\\root\\Office16\\EXCEL.EXE\" " + myListFilePath;

	system(command.c_str());
}

CSVFileRepository::~CSVFileRepository()
{
}
