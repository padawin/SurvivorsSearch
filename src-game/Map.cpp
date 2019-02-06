#include "Map.hpp"
#include "Collision.hpp"
#include "Actor.hpp"
#include <string.h>

Map::~Map() {
	if (visitedGrid != 0) {
		free(visitedGrid);
	}
}

void Map::init(int width, int height) {
	m_iWidth = width;
	m_iHeight = height;
	m_iSize = (unsigned) (width * height);
	visitedGrid = (char*) malloc(m_iSize * sizeof (char));
	memset(visitedGrid, 0, m_iSize);
}

unsigned int Map::getSize() const {
	return m_iSize;
}

int Map::getWidth() const {
	return m_iWidth;
}

int Map::getHeight() const {
	return m_iHeight;
}

E_TerrainType Map::getCell(const int x, const int y) const {
	return grid[_getCoordsKey(x, y)];
}

void Map::setCell(const int x, const int y, E_TerrainType c) {
	grid[_getCoordsKey(x, y)] = c;
}

void Map::addActor(std::shared_ptr<Actor> actor) {
	auto location = actor->getLocation();
	m_content.addActor(_getCoordsKey(location.x, location.y), actor);
}

void Map::removeActor(int x, int y) {
	m_content.removeActor(_getCoordsKey(x, y));
}

std::unordered_map<long unsigned, std::shared_ptr<Actor> > Map::getActors() {
	return m_content.getActors();
}

std::shared_ptr<Actor> Map::getActorAt(int x, int y) const {
	return m_content.getActorAt(_getCoordsKey(x, y));
}

unsigned long Map::_getCoordsKey(int x, int y) const {
	return (long unsigned) (y * getWidth() + x);
}

bool Map::moveActor(Actor* actor, int newX, int newY) {
	if (!isCellWalkable(newX, newY)) {
		return false;
	}

	auto location = actor->getLocation();
	long unsigned key = _getCoordsKey(location.x, location.y);
	long unsigned newKey = _getCoordsKey(newX, newY);
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

S_TileData Map::getTerrainTileData(int visibleNeighbours, int x, int y) {
	E_TerrainType type = getCell(x, y);
	Terrain *terrain = _getTerrain(type);
	E_TerrainTile tile = Terrain::getTerrainTile(
		type,
		terrain->hasFlag(Terrain::TERRAIN_FLAG_BASE) ?
			15 : _getSameNeighbours(x, y) | visibleNeighbours
	);
	if (m_mTerrainsTileData.find(tile) == m_mTerrainsTileData.end()) {
		S_TileData tileData;
		m_tilesManager.getResource(tile, tileData);
		m_mTerrainsTileData[tile] = tileData;
	}
	return m_mTerrainsTileData[tile];
}

int Map::_getSameNeighbours(int x, int y) {
	E_TerrainType type = getCell(x, y);
	int nbNeighbours = (y == 0 || getCell(x, y - 1) == type) // north
		+ NEIGHBOUR_WEST * (x == 0 || getCell(x - 1, y) == type) // west
		+ NEIGHBOUR_EAST * (x == getWidth() - 1 || getCell(x + 1, y) == type) // east
		+ NEIGHBOUR_SOUTH * (y == getHeight() - 1 || getCell(x, y + 1) == type); // south

	return nbNeighbours;
}
