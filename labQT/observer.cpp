#include "observer.h"

void Observable::notify()
{
	for (auto& obj : this->observables)
		obj->update();
}

void Observable::addObserver(Observer* obs)
{
	this->observables.push_back(obs);
}

void Observable::delObserver(Observer* obs)
{
	std::remove(this->observables.begin(), this->observables.end(), obs);
}
