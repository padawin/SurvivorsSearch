#ifndef __MAP_RENDERER__
#define __MAP_RENDERER__

#include "../types.hpp"
#include "../FieldOfView.hpp"

class Map;
class MapContent;
class MapRenderer {
	public:
	virtual	~MapRenderer() {}
	virtual void render(Map *map, FieldOfView &fov, int shiftX, int shiftY) = 0;
};

#endif
