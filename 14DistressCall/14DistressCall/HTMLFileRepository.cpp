#include "HTMLFileRepository.h"
#include <iostream>
#include <fstream>

using namespace std;

HTMLFileRepository::HTMLFileRepository(const std::string& fileName)
{
	this->fileName = fileName;
}

void HTMLFileRepository::addEvidenceFile(const EvidenceFile& evidenceFile)
{
	std::vector<EvidenceFile> evidenceFiles = this->loadDataFromFile();

	// check if the EvidenceFile is not already added
	for (auto evidence : evidenceFiles)
		if (evidence.getId() == evidenceFile.getId()) //the file already exists
			throw DatabaseException("The file already exists.");

	evidenceFiles.push_back(evidenceFile);

	this->storeDataToFile(evidenceFiles);
}

void HTMLFileRepository::deleteEvidenceFile(const std::string& evidenceFileToDeleteId)
{
	std::vector<EvidenceFile> evidenceFiles = loadDataFromFile();

	for (int indexEvidenceFile = 0; indexEvidenceFile < evidenceFiles.size(); indexEvidenceFile++)
		if (evidenceFiles[indexEvidenceFile].getId() == evidenceFileToDeleteId) // if the evidence file is found, delete it
		{
			evidenceFiles.erase(evidenceFiles.begin() + indexEvidenceFile);
			break;
		}

	storeDataToFile(evidenceFiles);
}

void HTMLFileRepository::updateEvidenceFile(const EvidenceFile& evidenceFileToUpdate)
{
	std::vector<EvidenceFile> evidenceFiles = loadDataFromFile();

	for (int indexEvidenceFile = 0; indexEvidenceFile < evidenceFiles.size(); indexEvidenceFile++)
		if (evidenceFiles[indexEvidenceFile].getId() == evidenceFileToUpdate.getId()) // if the evidence file is found, update it it
		{
			evidenceFiles[indexEvidenceFile] = evidenceFileToUpdate;
			break;
		}

	storeDataToFile(evidenceFiles);
}

std::vector<EvidenceFile> HTMLFileRepository::loadDataFromFile()
{
	ifstream inputStream;
	inputStream.open(this->fileName);

	vector<EvidenceFile> evidenceFilesDatabase{};

	std::string inputLine;
	// check if the file is empty
	getline(inputStream, inputLine);
	if (inputLine == "")
		return evidenceFilesDatabase;

	// read the next 13 lines
	int numberOfReadLines = 0;
	std::string endOfTable = "</table>";

	while (!inputStream.eof() && numberOfReadLines != 13)
	{
		getline(inputStream, inputLine);
		numberOfReadLines++;
	}

	std::string id, measurement, photograph;
	double imageClarityLevel;
	int quantity;

	// the first line contains "<tr>", the beginning of a new row, read and ignore it
	getline(inputStream, inputLine);
	while (!inputStream.eof() && inputLine != endOfTable)
	{
		// read 7 lines at a time

		//for each line ignore the first 4 characters and the last 5 characters ("<td>" "</td>")
		getline(inputStream, inputLine);
		inputLine = inputLine.erase(0, 4);
		inputLine = inputLine.erase(inputLine.size() - 5, 5);
		inputLine = inputLine.erase(inputLine.size() - 1, 1);
		id = inputLine;

		getline(inputStream, inputLine);
		inputLine = inputLine.erase(0, 4);
		inputLine = inputLine.erase(inputLine.size() - 5, 5);
		inputLine = inputLine.erase(inputLine.size() - 1, 1);
		measurement = inputLine;

		getline(inputStream, inputLine);
		inputLine = inputLine.erase(0, 4);
		inputLine = inputLine.erase(inputLine.size() - 5, 5);
		imageClarityLevel = atof(inputLine.c_str());

		getline(inputStream, inputLine);
		inputLine = inputLine.erase(0, 4);
		inputLine = inputLine.erase(inputLine.size() - 5, 5);
		quantity = atoi(inputLine.c_str());

		getline(inputStream, inputLine);
		inputLine = inputLine.erase(0, 4);
		inputLine = inputLine.erase(inputLine.size() - 5, 5);
		photograph = inputLine;

		// the last line contains "</tr>", the end of a row, read and ignore it
		getline(inputStream, inputLine);

		// create the EvidenceFile object
		EvidenceFile evidenceFile{ id, measurement, imageClarityLevel, quantity, photograph };
		ValidatorEvidenceFile::validateEvidenceFile(evidenceFile);
		evidenceFilesDatabase.push_back(evidenceFile);

		// read one more line so we cand compare it with the end of the table
		getline(inputStream, inputLine);
	}

	// read the last 2 lines
	numberOfReadLines = 0;

	while (!inputStream.eof() && numberOfReadLines != 2)
	{
		getline(inputStream, inputLine);
		numberOfReadLines++;
	}

	inputStream.close();
	return evidenceFilesDatabase;;
}


void HTMLFileRepository::storeDataToFile(std::vector<EvidenceFile> evidenceFiles)
{
	ofstream outputStream;
	outputStream.open(this->fileName, ios::out);

	// store to file the lines before the evidenceFiles
	outputStream << "<!DOCTYPE html>\n<html>\n<head>\n<title>MyList</title>\n</head>\n";
	outputStream << "<body>\n<table border = \"1\">\n";
	outputStream << "<tr>\n<td>Id</td>\n<td>Measurement</td>\n<td>ImageClarityLevel</td>\n<td>Quantity</td>\n<td>Photograph</td>\n</tr>\n";

	for (auto evidenceFile : evidenceFiles)
	{
		outputStream << "<tr>\n" << evidenceFile.EvidencefileAsStringHTMLFileFormat() << "\n</tr>\n";
	}

	// store the end lines
	outputStream << "</table>\n</body>\n</html>";

	outputStream.close();
}

void HTMLFileRepository::openExternal()
{
	std::string myListFilePath = this->fileName;
	std::string command = "\"C:\\Program Files (x86)\\Google\\Chrome\\Application\\chrome.exe\" " + myListFilePath;

	system(command.c_str());
}
