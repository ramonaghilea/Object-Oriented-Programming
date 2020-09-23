#include "Subject.h"

void Subject::registerObserver(Observer* observer)
{
	this->observers.push_back(observer);
}

void Subject::unregisterObserver(Observer* observer)
{
	auto positionObserverToRemove = std::find(this->observers.begin(), this->observers.end(), observer);
	if (positionObserverToRemove != this->observers.end())
		this->observers.erase(positionObserverToRemove);
}

void Subject::notify()
{
	for (auto observer : this->observers)
		observer->update();
}
