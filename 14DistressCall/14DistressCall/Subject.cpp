#include "Subject.h"

void Subject::registerObserver(Observer* observer)
{
	this->observers.push_back(observer);
}

void Subject::unregisterObserver(Observer* observer)
{
	auto iterator = std::find(this->observers.begin(), this->observers.end(), observer);
	if (iterator != this->observers.end())
	{
		this->observers.erase(iterator);
	}
}

void Subject::notify()
{
	for (auto observer : this->observers)
		observer->update();
}
