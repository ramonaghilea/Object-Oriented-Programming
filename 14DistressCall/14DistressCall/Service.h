#pragma once
#include "Repository.h"
#include "FileRepository.h"
#include "Exceptions.h"
#include "ValidatorEvidenceFile.h"
#include "Action.h"
#include "ActionAdd.h"
#include "ActionRemove.h"
#include "ActionUpdate.h"
#include "Subject.h"
#include <vector>
#include <memory>

using namespace std;

class Service: public Subject
{
private:
	Repository* repository;
	Repository* myListRepository;
	int currentIndex = 0;

	std::vector<unique_ptr<Action>> undoStack{};
	std::vector<unique_ptr<Action>> redoStack{};

	std::vector<unique_ptr<Action>> undoMyListStack{};
	std::vector<unique_ptr<Action>> redoMyListStack{};

public:
	Service(Repository* newRepository, Repository* newMyListRepository) : repository(newRepository), myListRepository(newMyListRepository) {};
	/*
		Adds an evidenceFile to the database.
		input: id, measurement, imageClarityLevel, quantity, photograph
		output: -
		throws: exception if the evidence file already exists.
	*/
	void addEvidenceFileService(const std::string& id, const std::string& measurement, const double& imageClarityLevel, const int& quantity, const std::string& photograph);
	/*
		Updates an evidenceFile in the database.
		input: id, measurement, imageClarityLevel, quantity, photograph
		output: -
		throws: exception if the evidence file does not exist.
	*/
	void updateEvidenceFileService(const std::string& id, const std::string& measurement, const double& imageClarityLevel, const int& quantity, const std::string& photograph);
	/*
		Deletes an evidenceFile from the database.
		input: id
		output: -
		throws: exception if the evidence file does not exist.
	*/
	void deleteEvidenceFileService(const std::string& evidenceFileId);

	/*
		Saves an evidenceFile to myList.
		input: id
		output: -
		throws: exception if the evidence file does not exist in the database.
				exception if the evidence file already exist in myList.
	*/
	void saveEvidenceFileToMyListService(const std::string& evidenceFileToBeSavedId);
	/*
		Returns all evidenceFiles.
		input: -
		output: - a dynamicVector containing all evidence files from the database
	*/
	std::vector<EvidenceFile> getAllEvidenceFilesService() const;

	/*
		Returns all evidenceFiles from myList.
		input: -
		output: - a dynamicVector containing all evidence files from myList
	*/
	std::vector<EvidenceFile> getAllEvidenceFilesFromMyListService() const;
	/*
		Returns all evidenceFiles with a specific measure and having minimum quantity.
		input: - measurement, minimum quantity
		output: - a dynamicVector containing all evidence files with specific measurement and minimum quantity
	*/
	std::vector<EvidenceFile> getFilteredEvidenceFilesAfterMeasurementAndMinimumQuantityService(const std::string& measurement, double minimumQuantity);
	/*
		Returns the next evidenceFile from the database.
		input: -
		output: - the next EvidenceFile
	*/
	EvidenceFile getNextEvidenceFileService();

	std::string getMyListFilePath() const;

	void setDatabaseFilePath(std::string& filePath);
	void setMyListFilePath(std::string& filePath);
	int getCurrentIndex();

	void openExternalMyList();

	void undo();
	void redo();
	
	void undoMyList();
	void redoMyList();

	~Service();
};
