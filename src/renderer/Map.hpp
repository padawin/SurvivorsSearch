#ifndef __MAP_RENDERER__
#define __MAP_RENDERER__

#include "../types.hpp"

class Map;
class MapContent;
class MapRenderer {
	public:
	virtual	~MapRenderer() {}
	virtual void render(Map &map, MapContent &content, S_Coordinates reference) = 0;
};

#endif
