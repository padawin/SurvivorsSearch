#include "NCursesMap.hpp"
#include <ncurses.h>
#include "../renderData.hpp"
#include "../Actor.hpp"
#include "../Map.hpp"
#include "../MapContent.hpp"
#include "../FieldOfView.hpp"

NCursesMap::NCursesMap() {
	m_view.x = 0;
	m_view.y = 0;
	m_view.width = 79;
	m_view.height = 29;
}

void NCursesMap::render(Map &map, S_Coordinates reference) {
	S_Rectangle visibleArea = m_view;
	visibleArea.x = reference.x - m_view.width / 2;
	visibleArea.y = reference.y - m_view.height / 2;
	FieldOfView fov(visibleArea);
	fov.calculate(map, reference);
	int displayShiftX = m_view.x - visibleArea.x;
	int displayShiftY = m_view.y - visibleArea.y;
	for (auto cell : fov.getVisibleCells(true)) {
		int x = cell.first.x,
			y = cell.first.y;
		mvaddstr(
			displayShiftY + y,
			displayShiftX + x,
			cell.second ? _getCellDisplayValue(map, x, y) : " "
		);
	}

	for (auto actor : map.getActors()) {
		actor.second->render(displayShiftX, displayShiftY);
	}
}

const char* NCursesMap::_getCellDisplayValue(Map &map, int x, int y) {
	if (x < 0 || x >= map.getWidth() ||
		y < 0 || y * map.getWidth() >= (signed) map.getSize()) {
		return " ";
	}

	return MAP_TILES[map.getCell(x, y)];
}
