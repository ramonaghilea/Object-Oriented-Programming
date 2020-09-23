#pragma once
#include "Action.h"
#include "Song.h"
#include "Repository.h"

class ActionAdd: public Action
{
private:
	Song addedSong;
	Repository& repository;

public:
	ActionAdd(Repository& repository, Song& song) : addedSong(song), repository(repository) {};
	void executeUndo() override;
	void executeRedo() override;
};

