#include "Collision.hpp"

const int Collision::terrainFlags[] = {
	FLAG_OBSTRUCTING_VIEW,
	FLAG_WALKABLE,
	FLAG_WALKABLE,
	FLAG_WALKABLE,
	FLAG_OBSTRUCTING_VIEW,
	0,
	FLAG_WALKABLE,
	FLAG_OBSTRUCTING_VIEW,
	FLAG_OBSTRUCTING_VIEW
};

bool Collision::hasFlag(int tile, int flag) {
	return Collision::terrainFlags[tile] & flag;
}
