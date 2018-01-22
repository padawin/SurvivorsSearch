#ifndef __OBSERVABLE__
#define __OBSERVABLE__

#include <vector>
#include "types.hpp"
#include "Observer.hpp"

class Actor;
class Observable {
	private:
	std::vector<Observer*> m_vObservers = {};

	public:
	virtual ~Observable() {}
	void addObserver(Observer *observer);
	void notify(E_Event event, Actor *actor = 0);
};

#endif
