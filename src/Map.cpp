#include "Map.hpp"

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
	m_content.addActor(actor);
}

std::vector<Actor*> Map::getActors() {
	return m_content.getActors();
}
