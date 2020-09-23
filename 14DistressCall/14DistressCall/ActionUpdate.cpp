#include "ActionUpdate.h"

void ActionUpdate::executeUndo()
{
	this->repository->updateEvidenceFile(oldEvidenceFile);
}

void ActionUpdate::executeRedo()
{
	this->repository->updateEvidenceFile(newEvidenceFile);
}
