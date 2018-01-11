#include <ncurses.h>
#include "Map.hpp"
#include "renderData.hpp"
#include "../Actor.hpp"
#include "../../Map.hpp"
#include "../../MapContent.hpp"

void NCursesMap::render(Map &map, FieldOfView &fov, int shiftX, int shiftY) {
	for (auto cell : fov.getVisibleCells(true)) {
		int x = cell.first.x,
			y = cell.first.y;
		mvaddstr(
			shiftY + y,
			shiftX + x,
			_getCellDisplayValue(map, cell.second, x, y)
		);
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
