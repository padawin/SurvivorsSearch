#include "Map.hpp"
#include "Collision.hpp"
#include "Actor.hpp"
#include <string.h>

Map::~Map() {
	if (grid != 0) {
		free(grid);
	}
	if (visitedGrid != 0) {
		free(visitedGrid);
	}
}

void Map::init() {
	m_iSize = (unsigned) (getWidth() * getHeight());
	grid = (char*) malloc(m_iSize * sizeof (char));
	visitedGrid = (char*) malloc(m_iSize * sizeof (char));
	memset(visitedGrid, 0, m_iSize);
}

unsigned int Map::getSize() const {
	return m_iSize;
}

unsigned char Map::getCell(const int x, const int y) const {
	return static_cast<unsigned char>(grid[_getCoordsKey(x, y)]);
}

void Map::setCell(const int x, const int y, char c) {
	grid[_getCoordsKey(x, y)] = c;
}

void Map::addActor(std::shared_ptr<Actor> actor) {
	auto location = actor->getLocation();
	m_content.addActor(_getCoordsKey(location.x, location.y), actor);
}

void Map::removeActor(int x, int y) {
	m_content.removeActor(_getCoordsKey(x, y));
}

std::unordered_map<int, std::shared_ptr<Actor> > Map::getActors() {
	return m_content.getActors();
}

std::shared_ptr<Actor> Map::getActorAt(int x, int y) const {
	return m_content.getActorAt(_getCoordsKey(x, y));
}

int Map::_getCoordsKey(int x, int y) const {
	return y * getWidth() + x;
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

bool Map::areCoordinatesValid(int x, int y) const {
	return x >= 0 && y >= 0 && x < getWidth() && y < getHeight();
}

bool Map::isCellWalkable(int x, int y) const {
	if (!areCoordinatesValid(x, y)) {
		return false;
	}

	bool walkable = (
		Collision::hasFlag(getCell(x, y), Collision::FLAG_WALKABLE) &&
		getActorAt(x, y) == NULL
	);

	return walkable;
}

bool Map::isCellObstructingView(int x, int y) const {
	return Collision::hasFlag(getCell(x, y), Collision::FLAG_OBSTRUCTING_VIEW);
}

bool Map::isCellVisited(int x, int y) const {
	return visitedGrid[_getCoordsKey(x, y)] == 1;
}

void Map::setCellVisited(int x, int y) {
	visitedGrid[_getCoordsKey(x, y)] = 1;
}
