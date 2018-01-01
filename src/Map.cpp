#include "Map.hpp"
#include "Actor.hpp"

int Map::getWidth() {
	return m_iWidth;
}

unsigned int Map::getSize() {
	return m_iSize;
}

unsigned char Map::getCell(const int x, const int y) const {
	int gridIndex = y * m_iWidth + x;
	return static_cast<unsigned char>(grid[gridIndex]);
}

void Map::addActor(Actor *actor) {
	auto location = actor->getLocation();
	m_content.addActor(_getCoordsKey(location.x, location.y), actor);
}

std::unordered_map<int, Actor*> Map::getActors() {
	return m_content.getActors();
}

int Map::_getCoordsKey(int x, int y) {
	return y * m_iWidth + x;
}

bool Map::moveActor(Actor* actor, int newX, int newY) {
	auto location = actor->getLocation();
	int key = _getCoordsKey(location.x, location.y);
	int newKey = _getCoordsKey(newX, newY);
	if (m_content.moveActor(key, newKey)) {
		actor->setX(newX);
		actor->setY(newY);
	}

	return true;
}
