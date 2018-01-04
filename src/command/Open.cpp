#include "Open.hpp"

bool OpenCommand::execute(Map &map, int xDest, int yDest, Actor *actor __attribute__((unused))) {
	if (map.getCell(xDest, yDest) == VERTIC_DOOR_TILE || map.getCell(xDest, yDest) == HORIZ_DOOR_TILE) {
		map.setCell(xDest, yDest, OPEN_DOOR_TILE);
		return true;
	}

	return false;
}
