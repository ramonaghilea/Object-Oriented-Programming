#include "Service.h"
#include <algorithm>
#include "FilePlaylist.h"
#include "RepositoryExceptions.h"

using namespace std;

void Service::addSongToRepository(const std::string& artist, const std::string& title, double minutes, double seconds, const std::string& source)
{
	Song s{ artist, title, Duration{minutes, seconds}, source };
	this->validator.validate(s);
	this->repo.addSong(s);

	unique_ptr<Action> addAction = make_unique<ActionAdd>(this->repo, s);
	this->undoStack.push_back(move(addAction));
}

void Service::removeSongFromRepository(const std::string & artist, const std::string & title)
{
	Song s = this->repo.findByArtistAndTitle(artist, title);
	this->repo.removeSong(s);

	unique_ptr<Action> removeAction = make_unique<ActionRemove>(this->repo, s);
	this->undoStack.push_back(move(removeAction));
}

void Service::updateSongInRepository(const std::string& artist, const std::string& title, double minutes, double seconds, const std::string& source)
{
	Song oldSong = this->repo.findByArtistAndTitle(artist, title);
	Song newSong{ artist, title, Duration{minutes, seconds}, source };
	this->validator.validate(newSong);
	this->repo.updateSong(newSong);

	unique_ptr<Action> updateAction = make_unique<ActionUpdate>(this->repo, oldSong, newSong);
	this->undoStack.push_back(move(updateAction));
}

void Service::addSongToPlaylist(const Song& song)
{
	if (this->playList == nullptr)
		return;
	this->playList->add(song);
}

void Service::addAllSongsByArtistToPlaylist(const std::string& artist)
{
	vector<Song> songs = this->repo.getSongs();
	int nSongs = static_cast<int>(count_if(songs.begin(), songs.end(),
		[artist](const Song& s)
		{
			return s.getArtist() == artist;
		}));

	vector<Song> songsByArtist(nSongs);
	copy_if(songs.begin(), songs.end(), songsByArtist.begin(),
		[artist](const Song& s)
		{
			return s.getArtist() == artist;
		});

	for (auto s : songsByArtist)
		this->playList->add(s);
}

void Service::startPlaylist()
{
	if (this->playList == nullptr)
		return;
	this->playList->play();
}

void Service::nextSongPlaylist()
{
	if (this->playList == nullptr)
		return;
	this->playList->next();
}

void Service::savePlaylist(const std::string& filename)
{
	if (this->playList == nullptr)
		return;

	this->playList->setFilename(filename);
	this->playList->writeToFile();
}

void Service::openPlaylist() const
{
	if (this->playList == nullptr)
		return;

	this->playList->displayPlaylist();
}

void Service::undo()
{
	if (this->undoStack.size() == 0)
		throw exception("No more undo.");
	unique_ptr<Action> undoAction = move(this->undoStack.back());
	this->undoStack.pop_back();
	undoAction->executeUndo();
	this->redoStack.push_back(move(undoAction));
}

void Service::redo()
{
	if (this->redoStack.size() == 0)
		throw exception("No more redo.");
	unique_ptr<Action> redoAction = move(this->redoStack.back());
	this->redoStack.pop_back();
	redoAction->executeRedo();
}
