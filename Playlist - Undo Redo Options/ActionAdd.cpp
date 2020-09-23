#include "ActionAdd.h"

void ActionAdd::executeUndo()
{
	this->repository.removeSong(this->addedSong);
}

void ActionAdd::executeRedo()
{
	this->repository.addSong(this->addedSong);
}
