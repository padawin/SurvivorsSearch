#include "Observable.hpp"
#include "Actor.hpp"

void Observable::_notify(E_Event event, Actor &actor) {
	for (auto observer : m_vObservers) {
		observer->onNotify(event, actor);
	}
}

void Observable::addObserver(Observer *observer) {
	m_vObservers.push_back(observer);
}
