#pragma once
#include "Action.h"
#include "Song.h"
#include "Repository.h"

class ActionUpdate : public Action
{
private:
	Song oldSong;
	Song newSong;
	Repository& repository;

public:
	ActionUpdate(Repository& repository, Song& oldSong, Song& newSong) : oldSong(oldSong), newSong(newSong), repository(repository) {};
	void executeUndo() override;
	void executeRedo() override;
};

