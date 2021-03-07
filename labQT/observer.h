#pragma once
#include <vector>
#include <algorithm>

class Observer
{
public:
	virtual void update() = 0;
	virtual ~Observer() = default;
};


class Observable
{
protected:
	std::vector<Observer*> observables;

public:
	void notify();

	void addObserver(Observer* obs);

	void delObserver(Observer* obs);
};