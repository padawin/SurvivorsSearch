#include "../Collision.hpp"

const char STONE_WALL_TILE = 0;
const char STONE_FLOOR_TILE = 1;

const int Collision::terrainFlags[] = {
	// STONE_WALL_TILE
	FLAG_OBSTRUCTING_VIEW,
	// STONE_FLOOR_TILE
	FLAG_WALKABLE
};
