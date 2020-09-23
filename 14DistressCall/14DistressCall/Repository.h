#pragma once
#include "Evidence.h"
#include "Exceptions.h"
#include <string>
#include <vector>

class Repository
{
public:
	// Repository();
	/*
		Adds an evidenceFile to the database.
		input: EvidenceFile
		output: -
	*/
	virtual void addEvidenceFile(const EvidenceFile& evidenceFile) = 0;
	/*
		Deletes an evidenceFile from the database.
		input: EvidenceFileId
		output: -
	*/
	virtual void deleteEvidenceFile(const std::string& evidenceFileId) = 0;
	/*
		Updates an evidenceFile in the database.
		input: EvidenceFile
		output: -
	*/
	virtual void updateEvidenceFile(const EvidenceFile& evidenceFile) = 0;


	/*
		Returns the evidenceFile by its id.
		input: id of EvidenceFile
		output: - the evidenceFile
	*/
	virtual EvidenceFile getEvidenceFileById(const std::string& Id) = 0;

	/*
		Returns all evidenceFiles from the database.
		input: -
		output: - a dynamicVector containing all evidence files from the database
	*/
	virtual std::vector<EvidenceFile> getAllEvidenceFiles() = 0;
	/*
		Returns the number of evidenceFiles from the database
		input:
		output: - integer representing the number of evidenceFiles
	*/
	virtual int getNumberEvidenceFiles() = 0;

	/*
		Returns all evidenceFiles with a specific measure and having minimum quantity.
		input: - measurement, minimum quantity
		output: - a dynamicVector containing all evidence files with specific measurement and minimum quantity
	*/
	virtual std::vector<EvidenceFile> getFilteredEvidenceFilesAfterMeasurementAndMinimumQuantity(const std::string& measurement, double minimumQuantity) = 0;

	// iterator
	/*
		Returns the next evidenceFile from the database.
		input: -
		output: - the next EvidenceFile
	*/
	virtual EvidenceFile getNextEvidenceFile() = 0;
	/*
		Sets the iterator to evidenceFiles.begin()
		input: -
		output: -
	*/
	virtual void restartIterator() = 0;

	virtual std::string getFilePath() const = 0;
	virtual void setFilePath(std::string& filePath) = 0;

	virtual int getCurrentIndex() = 0;
	virtual void openExternal() = 0;

	virtual ~Repository() {}
};