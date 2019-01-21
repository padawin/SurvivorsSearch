#ifndef __SDL2_MAP__
#define __SDL2_MAP__

#include "../../renderer/Map.hpp"
#include "../types.hpp"

class SDL2Map : public MapRenderer {
	S_Rectangle m_camera;

	public:
	SDL2Map();
	void render(Map *map, FieldOfView &fov, int shiftX, int shiftY);
	void setCamera(S_Rectangle camera);
};

#endif
