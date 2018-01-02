#include <ncurses.h>
#include "Map.hpp"
#include "renderData.hpp"
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
			_getCellDisplayValue(map, cell.second, x, y)
		);
	}

	for (auto actor : map.getActors()) {
		actor.second->render(displayShiftX, displayShiftY);
	}
}

const char* NCursesMap::_getCellDisplayValue(Map &map, int visible, int x, int y) {
	if (!map.areCoordinatesValid(x, y)) {
		return " ";
	}
	else if (visible) {
		return MAP_TILES[map.getCell(x, y)];
	}
	else if (map.isCellVisited(x, y)) {
		return MAP_TILES[map.getCell(x, y)];
	}

	return " ";
}
