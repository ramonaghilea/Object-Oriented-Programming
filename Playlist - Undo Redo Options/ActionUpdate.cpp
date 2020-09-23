#include "ActionUpdate.h"

void ActionUpdate::executeUndo()
{
	this->repository.updateSong(oldSong);
}

void ActionUpdate::executeRedo()
{
	this->repository.updateSong(newSong);
}
