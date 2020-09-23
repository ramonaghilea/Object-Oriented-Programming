#pragma once
#include "Action.h"
#include "Evidence.h"
#include "Repository.h"

class ActionUpdate : public Action
{
private:
	EvidenceFile oldEvidenceFile;
	EvidenceFile newEvidenceFile;
	Repository* repository;

public:
	ActionUpdate(Repository* repository, EvidenceFile& oldEvidenceFile, EvidenceFile& newEvidenceFile) : oldEvidenceFile(oldEvidenceFile), newEvidenceFile(newEvidenceFile), repository(repository) {};
	void executeUndo() override;
	void executeRedo() override;
};

