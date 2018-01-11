#ifndef __OBSERVABLE__
#define __OBSERVABLE__

#include <vector>
#include "types.hpp"
#include "Observer.hpp"

class Actor;
class Observable {
	private:
	std::vector<Observer*> m_vObservers = {};

	protected:
	void _notify(E_Event event, Actor &actor);

	public:
	virtual ~Observable() {}
	void addObserver(Observer *observer);
};

#endif
