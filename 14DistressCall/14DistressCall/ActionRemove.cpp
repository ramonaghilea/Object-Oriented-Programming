#include "ActionRemove.h"

void ActionRemove::executeUndo()
{
	this->repository->addEvidenceFile(this->deletedEvidenceFile);
}

void ActionRemove::executeRedo()
{
	this->repository->deleteEvidenceFile(this->deletedEvidenceFile.getId());
}
