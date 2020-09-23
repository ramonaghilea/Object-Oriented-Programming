#pragma once
#include "Action.h"
#include "Evidence.h"
#include "Repository.h"

class ActionRemove : public Action
{
private:
	EvidenceFile deletedEvidenceFile;
	Repository* repository;

public:
	ActionRemove(Repository* repository, EvidenceFile& EvidenceFile) : deletedEvidenceFile(EvidenceFile), repository(repository) {};
	void executeUndo() override;
	void executeRedo() override;
};
