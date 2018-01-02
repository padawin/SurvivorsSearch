#include "Map.hpp"
#include "Collision.hpp"
#include "Actor.hpp"

int Map::getWidth() {
	return m_iWidth;
}

unsigned int Map::getSize() {
	return m_iSize;
}

unsigned char Map::getCell(const int x, const int y) const {
	return static_cast<unsigned char>(grid[_getCoordsKey(x, y)]);
}

void Map::setCell(const int x, const int y, char c) {
	grid[_getCoordsKey(x, y)] = c;
}

void Map::addActor(Actor *actor) {
	auto location = actor->getLocation();
	m_content.addActor(_getCoordsKey(location.x, location.y), actor);
}

std::unordered_map<int, Actor*> Map::getActors() {
	return m_content.getActors();
}

Actor *Map::getActorAt(int x, int y) const {
	return m_content.getActorAt(_getCoordsKey(x, y));
}

int Map::_getCoordsKey(int x, int y) const {
	return y * m_iWidth + x;
}

bool Map::moveActor(Actor* actor, int newX, int newY) {
	if (!isCellWalkable(newX, newY)) {
		return false;
	}

	auto location = actor->getLocation();
	int key = _getCoordsKey(location.x, location.y);
	int newKey = _getCoordsKey(newX, newY);
	if (m_content.moveActor(key, newKey)) {
		actor->setX(newX);
		actor->setY(newY);
	}

	return true;
}

bool Map::areCoordinatesValid(int x, int y) {
	return x >= 0 && y >= 0 && x < m_iWidth && y < m_iHeight;
}

bool Map::isCellWalkable(int x, int y) {
	if (!areCoordinatesValid(x, y)) {
		return false;
	}

	return Collision::hasFlag(getCell(x, y), Collision::FLAG_WALKABLE);
}

bool Map::isCellObstructingView(int x, int y) {
	return Collision::hasFlag(getCell(x, y), Collision::FLAG_OBSTRUCTING_VIEW);
}

void Map::setCellVisited(int x, int y) {
	visitedGrid[_getCoordsKey(x, y)] = 1;
}
