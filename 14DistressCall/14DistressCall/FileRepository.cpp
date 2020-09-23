#include "FileRepository.h"
#include <algorithm>
#include <iostream>
#include <fstream>

using namespace std;

FileRepository::FileRepository()
{
	this->currentPositionEvidenceFiles = 0;
}

FileRepository::FileRepository(const std::string& fileName)
{
	this->fileName = fileName;
	this->currentPositionEvidenceFiles = 0;
}

void FileRepository::addEvidenceFile(const EvidenceFile& evidenceFile)
{
	std::vector<EvidenceFile> evidenceFiles = this->loadDataFromFile();

	// check if the EvidenceFile is not already added
	for(auto evidence: evidenceFiles)
		if(evidence.getId() == evidenceFile.getId()) //the file already exists
			throw DatabaseException("The file already exists.");

	evidenceFiles.push_back(evidenceFile);
	this->storeDataToFile(evidenceFiles);
}

void FileRepository::deleteEvidenceFile(const std::string& evidenceFileToDeleteId)
{
	std::vector<EvidenceFile> evidenceFiles = loadDataFromFile();
	bool isEvidenceFileDeleted = false;

	for(int indexEvidenceFile = 0; indexEvidenceFile < evidenceFiles.size(); indexEvidenceFile++)
		if (evidenceFiles[indexEvidenceFile].getId() == evidenceFileToDeleteId) // if the evidence file is found, delete it
		{
			evidenceFiles.erase(evidenceFiles.begin() + indexEvidenceFile);
			isEvidenceFileDeleted = true;
			break;
		}

	if (!isEvidenceFileDeleted) // the id does not exist
		throw DatabaseException("The file does not exist.");

	storeDataToFile(evidenceFiles);
}

void FileRepository::updateEvidenceFile(const EvidenceFile& evidenceFileToUpdate)
{
	std::vector<EvidenceFile> evidenceFiles = loadDataFromFile();
	bool isEvidenceFileUpdated = false;

	for (int indexEvidenceFile = 0; indexEvidenceFile < evidenceFiles.size(); indexEvidenceFile++)
		if (evidenceFiles[indexEvidenceFile].getId() == evidenceFileToUpdate.getId()) // if the evidence file is found, update it it
		{
			evidenceFiles[indexEvidenceFile] = evidenceFileToUpdate;
			isEvidenceFileUpdated = true;
			break;
		}

	if (!isEvidenceFileUpdated) // the id does not exist
		throw DatabaseException("The file does not exist.");

	storeDataToFile(evidenceFiles);
}

EvidenceFile FileRepository::getEvidenceFileById(const std::string& EvidenceFileId)
{
	std::vector<EvidenceFile> evidenceFiles = loadDataFromFile();

	for (auto evidenceFile : evidenceFiles)
		if (evidenceFile.getId() == EvidenceFileId)
			return evidenceFile;

	// if the file does not exist, throw error
	throw DatabaseException("The file does not exist in the database.");
}

std::vector<EvidenceFile> FileRepository::getAllEvidenceFiles()
{
	std::vector<EvidenceFile> evidenceFiles = loadDataFromFile();
	return evidenceFiles;
}

int FileRepository::getNumberEvidenceFiles()
{
	std::vector<EvidenceFile> evidenceFiles = loadDataFromFile();
	return static_cast<int>(evidenceFiles.size());
}

std::vector<EvidenceFile> FileRepository::getFilteredEvidenceFilesAfterMeasurementAndMinimumQuantity(const std::string& measurement, double minimumQuantity)
{
	std::vector<EvidenceFile> evidenceFiles = loadDataFromFile();

	std::vector<EvidenceFile> filteredEvidenceFilesAfterMeasurementAndMinimumQuantity;

	std::copy_if(evidenceFiles.begin(), evidenceFiles.end(), std::back_inserter(filteredEvidenceFilesAfterMeasurementAndMinimumQuantity), [minimumQuantity, measurement](EvidenceFile evidence) {return (evidence.getQuantity() >= minimumQuantity) && evidence.getMeasurement() == measurement; });

	return filteredEvidenceFilesAfterMeasurementAndMinimumQuantity;
}


EvidenceFile FileRepository::getNextEvidenceFile()
{
	std::vector<EvidenceFile> evidenceFiles = loadDataFromFile();

	if (this->currentPositionEvidenceFiles == evidenceFiles.size())
		this->currentPositionEvidenceFiles = 0;

	return evidenceFiles[this->currentPositionEvidenceFiles++];
}

void FileRepository::restartIterator()
{
	this->currentPositionEvidenceFiles = 0;
}

std::vector<EvidenceFile> FileRepository::loadDataFromFile()
{
	ifstream inputStream;
	inputStream.open(this->fileName);

	vector<EvidenceFile> evidenceFilesDatabase{};
	EvidenceFile evidenceFile;

	while (inputStream >> evidenceFile) // read while the boolean value of inputStream(ifstream) is true
	{
		evidenceFilesDatabase.push_back(evidenceFile);
	}

	inputStream.close();
	return evidenceFilesDatabase;
}

void FileRepository::storeDataToFile(std::vector<EvidenceFile> evidenceFiles)
{
	ofstream outputStream;
	outputStream.open(this->fileName, ios::out);

	for (auto evidenceFile : evidenceFiles)
		outputStream << evidenceFile;

	outputStream.close();
}

//void FileRepository::clearDataFromFile()
//{
//	ofstream outputStream;
//	outputStream.open(this->fileName);
//	outputStream.close();
//}

std::string FileRepository::getFilePath() const
{
	return this->fileName;
}

void FileRepository::setFilePath(std::string& filePath)
{
	this->fileName = filePath;
}

int FileRepository::getCurrentIndex()
{
	std::vector<EvidenceFile> evidenceFiles = loadDataFromFile();

	// the special case is when there is only one element in the database
	if (currentPositionEvidenceFiles == 1 && evidenceFiles.size() == 1)
		return 0;

	int currentIndex = this->currentPositionEvidenceFiles - 1;
	return currentIndex;
}

void FileRepository::openExternal()
{
	std::string command = "start " + this->fileName;

	system(command.c_str());
}

FileRepository::~FileRepository()
{
}

