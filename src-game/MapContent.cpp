#include "MapContent.hpp"
#include "Actor.hpp"

void MapContent::addActor(long unsigned position, std::shared_ptr<Actor> actor) {
	m_mActors[position] = actor;
}

void MapContent::removeActor(long unsigned position) {
	m_mActors.erase(position);
}

std::unordered_map<long unsigned, std::shared_ptr<Actor> > &MapContent::getActors() {
	return m_mActors;
}

bool MapContent::moveActor(long unsigned oldPosition, long unsigned newPosition) {
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

std::shared_ptr<Actor> MapContent::getActorAt(long unsigned key) const {
	auto it = m_mActors.find(key);
	if (it != m_mActors.end()) {
		return it->second;
	}

	return NULL;
}
