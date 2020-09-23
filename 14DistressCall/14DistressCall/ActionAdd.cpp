#include "ActionAdd.h"

void ActionAdd::executeUndo()
{
	this->repository->deleteEvidenceFile(this->addedEvidenceFile.getId());
}

void ActionAdd::executeRedo()
{
	this->repository->addEvidenceFile(this->addedEvidenceFile);
}
