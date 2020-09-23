#pragma once
#include "Repository.h"
#include "ValidatorEvidenceFile.h"

class FileRepository : public Repository
{
protected:
	std::string fileName;
	int currentPositionEvidenceFiles;

public:
	FileRepository();
	FileRepository(const std::string& fileName);

	virtual void addEvidenceFile(const EvidenceFile& evidenceFile) override;
	virtual void deleteEvidenceFile(const std::string& evidenceFileToDeleteId) override;
	virtual void updateEvidenceFile(const EvidenceFile& evidenceFileToUpdate) override;

	EvidenceFile getEvidenceFileById(const std::string& Id) override;

	std::vector<EvidenceFile> getAllEvidenceFiles() override;
	int getNumberEvidenceFiles() override;

	std::vector<EvidenceFile> getFilteredEvidenceFilesAfterMeasurementAndMinimumQuantity(const std::string& measurement, double minimumQuantity) override;


	// iterator

	EvidenceFile getNextEvidenceFile() override;
	void restartIterator() override;

	// load data/ store data

	/*
		Loads the evidenceFiles from file.
		input: -
		output: a vector containing the evidenceFiles
	*/
	virtual std::vector<EvidenceFile> loadDataFromFile();
	/*
		Stores the evidenceFiles to file.
		input: vector of EvidenceFiles
		output: -
	*/
	virtual void storeDataToFile(std::vector<EvidenceFile> evidenceFiles);
	/*
		Clear the data from a file.
		input: -
		output: -
	*/
	//void clearDataFromFile();

	virtual std::string getFilePath() const override;
	virtual void setFilePath(std::string& filePath) override;

	int getCurrentIndex() override;
	virtual void openExternal() override;

	virtual ~FileRepository() override;
};


