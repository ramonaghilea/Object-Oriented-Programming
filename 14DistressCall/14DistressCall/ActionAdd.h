#pragma once
#include "Action.h"
#include "Evidence.h"
#include "Repository.h"

class ActionAdd: public Action
{
private:
	EvidenceFile addedEvidenceFile;
	Repository* repository;

public:
	ActionAdd(Repository* repository, EvidenceFile& EvidenceFile) : addedEvidenceFile(EvidenceFile), repository(repository) {};
	void executeUndo() override;
	void executeRedo() override;
};

