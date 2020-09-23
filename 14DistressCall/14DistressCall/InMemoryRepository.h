#pragma once
#include "Repository.h"

class InMemoryRepository : public Repository
{
private:
	std::vector<EvidenceFile> evidenceFiles;
	std::vector<EvidenceFile> myListOfEvidenceFiles;
	int currentPositionEvidenceFiles;

public:
	InMemoryRepository();

	void addEvidenceFile(const EvidenceFile& evidenceFile) override;
	void deleteEvidenceFile(const std::string& evidenceFileId) override;
	void updateEvidenceFile(const EvidenceFile& evidenceFile) override;

	EvidenceFile getEvidenceFileById(const std::string& Id) override;

	std::vector<EvidenceFile> getAllEvidenceFiles() override;
	int getNumberEvidenceFiles() override;

	// myList functions

	std::vector<EvidenceFile> getFilteredEvidenceFilesAfterMeasurementAndMinimumQuantity(const std::string& measurement, double minimumQuantity) override;

	// iterator

	EvidenceFile getNextEvidenceFile() override;
	void restartIterator() override;

	std::string getFilePath() const override;
	void setFilePath(std::string& filePath) override;
	int getCurrentIndex() override;
	void openExternal() override;

	~InMemoryRepository();
};
