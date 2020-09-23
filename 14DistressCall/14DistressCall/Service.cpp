#include "Service.h"
#include "CSVFileRepository.h"
#include "HTMLFileRepository.h"
#include <memory>

using namespace std;

void Service::addEvidenceFileService(const std::string& id, const std::string& measurement, const double& imageClarityLevel, const int& quantity, const std::string& photograph)
{
	// set the iterator to point to the first sample of evidence everytime a commmand different from next is entered
	this->repository->restartIterator();
	this->currentIndex = 0;

	EvidenceFile evidenceFileToAdd{ id, measurement, imageClarityLevel, quantity, photograph }; // create the evidenceFile object
	ValidatorEvidenceFile::validateEvidenceFile(evidenceFileToAdd); // validate the evidenceFile to be added
	this->repository->addEvidenceFile(evidenceFileToAdd);

	unique_ptr<Action> addAction = make_unique<ActionAdd>(this->repository, evidenceFileToAdd);
	this->undoStack.push_back(move(addAction));
}

void Service::updateEvidenceFileService(const std::string& id, const std::string& measurement, const double& imageClarityLevel, const int& quantity, const std::string& photograph)
{
	// set the iterator to point to the first sample of evidence everytime a commmand different from next is entered
	this->repository->restartIterator();
	this->currentIndex = 0;

	EvidenceFile oldEvidenceFile = this->repository->getEvidenceFileById(id);
	EvidenceFile evidenceFileToUpdate{ id, measurement, imageClarityLevel, quantity, photograph };
	ValidatorEvidenceFile::validateEvidenceFile(evidenceFileToUpdate); // validate the evidenceFile to be updated
	this->repository->updateEvidenceFile(evidenceFileToUpdate);

	unique_ptr<Action> updateAction = make_unique<ActionUpdate>(this->repository, oldEvidenceFile, evidenceFileToUpdate);
	this->undoStack.push_back(move(updateAction));

	try
	{
		this->myListRepository->updateEvidenceFile(evidenceFileToUpdate);
		// notify the observer that some changes have been made (update the second window)
		this->notify();
	}
	catch (exception&)
	{
		return;
	}
}

void Service::deleteEvidenceFileService(const std::string& evidenceFileId)
{
	// set the iterator to point to the first sample of evidence everytime a commmand different from next is entered
	this->repository->restartIterator();
	this->currentIndex = 0;

	EvidenceFile evidenceFileToDelete = this->repository->getEvidenceFileById(evidenceFileId);
	this->repository->deleteEvidenceFile(evidenceFileId);

	unique_ptr<Action> removeAction = make_unique<ActionRemove>(this->repository, evidenceFileToDelete);
	this->undoStack.push_back(move(removeAction));

	try
	{
		this->myListRepository->deleteEvidenceFile(evidenceFileId);
		// notify the observer that some changes have been made (update the second window)
		this->notify();
	}
	catch (exception&)
	{
		return;
	}

}

void Service::saveEvidenceFileToMyListService(const std::string& evidenceFileToBeSavedId)
{
	// set the iterator to point to the first sample of evidence everytime a commmand different from next is entered
	//this->repository->restartIterator();

	ValidatorId::validateId(evidenceFileToBeSavedId);
	// if the EvidenceFile does not exist in the database, it will throw an error
	EvidenceFile evidence = this->repository->getEvidenceFileById(evidenceFileToBeSavedId);

	// if the evidenceFile exists in the database, save it to myList
	//EvidenceFile copyEvidence{ evidence }; // make a copy of the evidenceFile
	this->myListRepository->addEvidenceFile(evidence); // save the copy of the evidence to my list

	unique_ptr<Action> addAction = make_unique<ActionAdd>(this->myListRepository, evidence);
	this->undoMyListStack.push_back(move(addAction));

	// notify the observer that some changes have been made (update the second window)
	this->notify();
}

std::vector<EvidenceFile> Service::getAllEvidenceFilesService() const
{
	// set the iterator to point to the first sample of evidence everytime a commmand different from next is entered
	//this->repository->restartIterator();

	return this->repository->getAllEvidenceFiles();
}

std::vector<EvidenceFile> Service::getAllEvidenceFilesFromMyListService() const
{
	// set the iterator to point to the first sample of evidence everytime a commmand different from next is entered
	//this->repository->restartIterator();

	return this->myListRepository->getAllEvidenceFiles();
}

std::vector<EvidenceFile> Service::getFilteredEvidenceFilesAfterMeasurementAndMinimumQuantityService(const std::string& measurement, double minimumQuantity)
{
	// set the iterator to point to the first sample of evidence everytime a commmand different from next is entered
	this->repository->restartIterator();
	this->currentIndex = 0;

	return this->repository->getFilteredEvidenceFilesAfterMeasurementAndMinimumQuantity(measurement, minimumQuantity);
}

EvidenceFile Service::getNextEvidenceFileService()
{
	this->currentIndex++;

	return this->repository->getNextEvidenceFile();
}

std::string Service::getMyListFilePath() const
{
	return this->myListRepository->getFilePath();
}

void Service::setDatabaseFilePath(std::string& filePath)
{	
	this->repository->setFilePath(filePath);
}

void Service::setMyListFilePath(std::string& filePath)
{
	this->myListRepository->setFilePath(filePath);
}

int Service::getCurrentIndex()
{
	return this->repository->getCurrentIndex();
}


void Service::openExternalMyList()
{
	this->myListRepository->openExternal();
}

void Service::undo()
{
	if (this->undoStack.size() == 0)
		throw exception("No more undo.");
	unique_ptr<Action> undoAction = move(this->undoStack.back());
	this->undoStack.pop_back();
	undoAction->executeUndo();
	this->redoStack.push_back(move(undoAction));
}

void Service::redo()
{
	if (this->redoStack.size() == 0)
		throw exception("No more redo.");
	unique_ptr<Action> redoAction = move(this->redoStack.back());
	this->redoStack.pop_back();
	redoAction->executeRedo();
	this->undoStack.push_back(move(redoAction));
}

void Service::undoMyList()
{
	if (this->undoMyListStack.size() == 0)
		throw exception("No more undo.");
	unique_ptr<Action> undoAction = move(this->undoMyListStack.back());
	this->undoMyListStack.pop_back();
	undoAction->executeUndo();
	this->redoMyListStack.push_back(move(undoAction));

	// notify the observer that some changes have been made (update the second window)
	this->notify();
}

void Service::redoMyList()
{
	if (this->redoMyListStack.size() == 0)
		throw exception("No more redo.");
	unique_ptr<Action> redoAction = move(this->redoMyListStack.back());
	this->redoMyListStack.pop_back();
	redoAction->executeRedo();
	this->undoMyListStack.push_back(move(redoAction));

	// notify the observer that some changes have been made (update the second window)
	this->notify();
}

Service::~Service()
{
}
