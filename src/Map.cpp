#include "Map.hpp"
#include "Actor.hpp"

int Map::getWidth() {
	return width;
}

unsigned int Map::getSize() {
	return size;
}

unsigned char Map::getCell(const int x, const int y) const {
	int gridIndex = y * width + x;
	return static_cast<unsigned char>(grid[gridIndex]);
}

void Map::addActor(Actor *actor) {
	auto location = actor->getLocation();
	m_content.addActor(location.y * (signed) size + location.x, actor);
}

std::unordered_map<int, Actor*> Map::getActors() {
	return m_content.getActors();
}
