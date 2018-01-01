#include "MapContent.hpp"
#include "Actor.hpp"

void MapContent::addActor(int position, Actor *actor) {
	m_mActors[position] = actor;
}

std::unordered_map<int, Actor*> &MapContent::getActors() {
	return m_mActors;
}

bool MapContent::moveActor(int oldPosition, int newPosition) {
	auto it = m_mActors.find(oldPosition);
	if (it == m_mActors.end()) {
		return false;
	}

	// Swap value from oldKey to newKey, note that a default constructed value
	// is created by operator[] if 'm_mActors' does not contain newKey.
	std::swap(m_mActors[newPosition], it->second);

	// Erase old key-value from map
	m_mActors.erase(it);
	return true;
}
