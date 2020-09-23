#pragma once
#include "Action.h"
#include "Song.h"
#include "Repository.h"

class ActionRemove : public Action
{
private:
	Song deletedSong;
	Repository& repository;

public:
	ActionRemove(Repository& repository, Song& song) : deletedSong(song), repository(repository) {};
	void executeUndo() override;
	void executeRedo() override;
};
