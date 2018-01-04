#include "Collision.hpp"

const int Collision::terrainFlags[] = {
	// WALL_TILE
	FLAG_OBSTRUCTING_VIEW,
	// ROAD_TILE
	FLAG_WALKABLE,
	// PAVEMENT_TILE
	FLAG_WALKABLE,
	// GRASS_TILE
	FLAG_WALKABLE,
	// TREE_TILE
	FLAG_OBSTRUCTING_VIEW,
	// WATER_TILE
	0,
	// INTERIOR_TILE
	FLAG_WALKABLE,
	// HORIZ_DOOR_TILE
	FLAG_OBSTRUCTING_VIEW,
	// VERTIC_DOOR_TILE
	FLAG_OBSTRUCTING_VIEW,
	// OPEN_DOOR_TILE
	FLAG_WALKABLE
};

bool Collision::hasFlag(int tile, int flag) {
	return Collision::terrainFlags[tile] & flag;
}
