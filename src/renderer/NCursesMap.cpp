#include "NCursesMap.hpp"
#include <ncurses.h>
#include "../renderData.hpp"
#include "../Actor.hpp"
#include "../Map.hpp"
#include "../MapContent.hpp"

NCursesMap::NCursesMap() {
	m_view.x = 0;
	m_view.y = 0;
	m_view.width = 79;
	m_view.height = 29;
}

void NCursesMap::render(Map &map, S_Coordinates reference) {
	// coordinates in the world
	int topLeftX = reference.x - m_view.width / 2,
		topLeftY = reference.y - m_view.height / 2,
		bottomRightX = reference.x + m_view.width / 2,
		bottomRightY = reference.y + m_view.height / 2;
	for (int y = topLeftY; y < bottomRightY; ++y) {
		for (int x = topLeftX; x < bottomRightX; ++x) {
			mvaddstr(
				m_view.y + y - topLeftY,
				m_view.x + x - topLeftX,
				_getCellDisplayValue(map, x, y)
			);
		}
	}

	for (auto actor : map.getActors()) {
		actor.second->render(m_view.x - topLeftX, m_view.y - topLeftY);
	}
}

const char* NCursesMap::_getCellDisplayValue(Map &map, int x, int y) {
	if (x < 0 || x > map.getWidth() ||
		y < 0 || y * map.getWidth() > (signed) map.getSize()) {
		return " ";
	}

	return MAP_TILES[map.getCell(x, y)];
}
