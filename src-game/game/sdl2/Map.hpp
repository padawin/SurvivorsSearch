#ifndef __SDL2_MAP__
#define __SDL2_MAP__

#include "../../renderer/Map.hpp"
#include "../../Map.hpp"
#include "../graphic/Factory.hpp"
#include "TextureManager.hpp"
#include "types.hpp"

class SDL2Map : public MapRenderer {
	S_Rectangle m_camera;
	GraphicFactory m_graphicFactory;

	void _renderTerrain(TextureManager *manager, const SDL2Renderer *renderer, Map *map, FieldOfView &fov, int displayShiftX, int displayShiftY, int x, int y);
	// void _renderObjects(TextureManager *manager, int displayShiftX, int displayShiftY, int x, int y);
	// void _renderActors(int displayShiftX, int displayShiftY, int x, int y);
	int _getMaskVisibleNeighbours(FieldOfView &fov, int x, int y);

	public:
	SDL2Map();
	void render(const Renderer *renderer, Map *map, FieldOfView &fov, int shiftX, int shiftY);
	void setCamera(S_Rectangle camera);
};

#endif
