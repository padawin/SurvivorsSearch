#include "MapContent.hpp"
#include "Actor.hpp"

void MapContent::addActor(Actor *actor) {
	m_vActors.push_back(actor);
}

std::vector<Actor*> &MapContent::getActors() {
	return m_vActors;
}
