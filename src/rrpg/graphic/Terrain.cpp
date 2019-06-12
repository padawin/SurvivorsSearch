#include "./Terrain.hpp"
#include "../sdl2/TextureManager.hpp"

void GraphicTerrain::render(
	TextureManager *manager,
	const SDL2Renderer *renderer,
	int displayShiftX,
	int displayShiftY,
	S_TileData tileData,
	S_Coordinates tilePosition
) {
	int xScreen = tilePosition.x * tileData.width + displayShiftX,
		yScreen = tilePosition.y * tileData.height + displayShiftY;

	// the rows are 1 based, and the columns are 0 based, which is
	// stupid
	manager->drawTile(
		tileData.tileset,
		0, // margin
		0, // spacing
		xScreen,
		yScreen,
		tileData.width,
		tileData.height,
		tileData.y + 1,
		tileData.x,
		renderer->getRenderer()
	);
}
