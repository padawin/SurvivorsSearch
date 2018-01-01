#include "MapContent.hpp"
#include "Actor.hpp"

void MapContent::addActor(int position, Actor *actor) {
	m_mActors[position] = actor;
}

std::unordered_map<int, Actor*> &MapContent::getActors() {
	return m_mActors;
}
