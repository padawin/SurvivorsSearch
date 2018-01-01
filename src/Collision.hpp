#ifndef __COLLISION__
#define __COLLISION__

class Collision {
	public:
	static const int FLAG_WALKABLE = 1;
	static const int FLAG_OBSTRUCTING_VIEW = 2;

	static const int terrainFlags[];

	static bool hasFlag(int tile, int flag);
};

#endif
