#ifndef __MAP_RENDERER__
#define __MAP_RENDERER__

#include "../types.hpp"

class Map;
class MapRenderer {
	public:
	virtual	~MapRenderer() {}
	virtual void render(Map &map, S_Coordinates reference) = 0;
};

#endif
