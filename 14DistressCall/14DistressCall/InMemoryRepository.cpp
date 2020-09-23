#include "InMemoryRepository.h"
#include <algorithm>
#include <iostream>
#include <fstream>

using namespace std;

InMemoryRepository::InMemoryRepository()
{
	this->currentPositionEvidenceFiles = 0;
}

void InMemoryRepository::addEvidenceFile(const EvidenceFile& evidenceFile)
{
	this->evidenceFiles.push_back(evidenceFile);
}

void InMemoryRepository::deleteEvidenceFile(const std::string& evidenceFileId)
{
	int indexEvidenceFileToDelete = -1;

	for (int index = 0; index < this->evidenceFiles.size(); index++)
		if (this->evidenceFiles[index].getId() == evidenceFileId)
			indexEvidenceFileToDelete = index;

	this->evidenceFiles.erase(this->evidenceFiles.begin() + indexEvidenceFileToDelete);

}

void InMemoryRepository::updateEvidenceFile(const EvidenceFile& evidenceFile)
{
	int indexEvidenceFileToUpdate = -1;

	for (int index = 0; index < this->evidenceFiles.size(); index++)
		if (this->evidenceFiles[index].getId() == evidenceFile.getId())
			indexEvidenceFileToUpdate = index;

	this->evidenceFiles[indexEvidenceFileToUpdate] = evidenceFile;
}

EvidenceFile InMemoryRepository::getEvidenceFileById(const std::string& Id)
{
	for (auto evidenceFile : this->evidenceFiles)
	{
		if (evidenceFile.getId() == Id)
			return evidenceFile;
	}
	throw "The id does not exist.";
}

std::vector<EvidenceFile> InMemoryRepository::getAllEvidenceFiles()
{
	return this->evidenceFiles;
}

int InMemoryRepository::getNumberEvidenceFiles()
{
	return static_cast<int>(this->evidenceFiles.size());
}

std::vector<EvidenceFile> InMemoryRepository::getFilteredEvidenceFilesAfterMeasurementAndMinimumQuantity(const std::string& measurement, double minimumQuantity)
{

	std::vector<EvidenceFile> filteredEvidenceFilesAfterMeasurementAndMinimumQuantity;

	std::copy_if(this->evidenceFiles.begin(), this->evidenceFiles.end(), std::back_inserter(filteredEvidenceFilesAfterMeasurementAndMinimumQuantity), [minimumQuantity, measurement](EvidenceFile evidence) {return (evidence.getQuantity() >= minimumQuantity) && evidence.getMeasurement() == measurement; });

	return filteredEvidenceFilesAfterMeasurementAndMinimumQuantity;
}

EvidenceFile InMemoryRepository::getNextEvidenceFile()
{
	if (this->currentPositionEvidenceFiles == this->evidenceFiles.size())
		this->currentPositionEvidenceFiles = 0;

	return this->evidenceFiles[this->currentPositionEvidenceFiles++];
}

void InMemoryRepository::restartIterator()
{
	this->currentPositionEvidenceFiles = 0;
}

std::string InMemoryRepository::getFilePath() const
{
	return "";
}

void InMemoryRepository::setFilePath(std::string& filePath)
{
}

int InMemoryRepository::getCurrentIndex()
{
	if (this->currentPositionEvidenceFiles == 1 && this->evidenceFiles.size() == 1)
		return 0;
	else if (this->currentPositionEvidenceFiles == 0)
		return this->evidenceFiles.size() - 1;

	int currentIndex = this->currentPositionEvidenceFiles - 1;
	return currentIndex;
}

void InMemoryRepository::openExternal()
{
}

InMemoryRepository::~InMemoryRepository()
{
}
