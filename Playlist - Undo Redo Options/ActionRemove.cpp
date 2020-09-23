#include "ActionRemove.h"

void ActionRemove::executeUndo()
{
	this->repository.addSong(this->deletedSong);
}

void ActionRemove::executeRedo()
{
	this->repository.removeSong(this->deletedSong);
}
