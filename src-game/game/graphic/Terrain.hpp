#ifndef __GRAPHIC_TERRAIN__
#define __GRAPHIC_TERRAIN__

#include "Graphic.hpp"
#include "types.hpp"
#include "commonTypes.hpp"
#include "../sdl2/Renderer.hpp"

class TextureManager;

class GraphicTerrain : public Graphic {
	public:
	void render(
		TextureManager *manager,
		const SDL2Renderer *renderer,
		int displayShiftX,
		int displayShiftY,
		S_TileData tileData,
		S_Coordinates tilePosition
	);
};

#endif
