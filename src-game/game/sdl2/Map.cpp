#include "Map.hpp"
#include <iostream>

SDL2Map::SDL2Map() :
	m_camera(),
	m_graphicFactory(GraphicFactory())
{
}

void SDL2Map::render(const Renderer *renderer, Map *map, FieldOfView &fov, int shiftX, int shiftY) {
	TextureManager *manager = TextureManager::Instance();
	std::cout << "Render map\n";

	int displayShiftX = m_camera.x - shiftX;
	int displayShiftY = m_camera.y - shiftY;
	for (auto cell : fov.getVisibleCells(true)) {
		int x = cell.first.x,
			y = cell.first.y;
		_renderTerrain(
			manager,
			(const SDL2Renderer*) renderer,
			map,
			fov,
			displayShiftX,
			displayShiftY,
			x,
			y
		);
		// _renderObjects(manager, game, displayShiftX, displayShiftY, x, y);
		// _renderActors(displayShiftX, displayShiftY, x, y);
	}
}

void SDL2Map::setCamera(S_Rectangle camera) {
	m_camera = camera;
}

void SDL2Map::_renderTerrain(
	TextureManager *manager,
	const SDL2Renderer *renderer,
	Map *map,
	FieldOfView &fov,
	int displayShiftX,
	int displayShiftY,
	int x, int y
) {
	int mask = _getMaskVisibleNeighbours(fov, x, y);
	S_TileData tileData = map->getTerrainTileData(mask, x, y);
	S_Coordinates position;
	position.x = x;
	position.y = y;
	m_graphicFactory.getGraphicTerrain()->render(
		manager,
		renderer,
		displayShiftX,
		displayShiftY,
		tileData,
		position
	);
}

int SDL2Map::_getMaskVisibleNeighbours(FieldOfView &fov, int x, int y) {
	int width = fov.getVisibleArea().width,
		height = fov.getVisibleArea().height;
	int nbNeighbours = (y == 0 || !fov.isVisible(x, y - 1)) // north
		+ NEIGHBOUR_WEST * (x == 0 || !fov.isVisible(x - 1, y)) // west
		+ NEIGHBOUR_EAST * (x == width - 1 || !fov.isVisible(x + 1, y)) // east
		+ NEIGHBOUR_SOUTH * (y == height - 1 || !fov.isVisible(x, y + 1)); // south

	return nbNeighbours;
}

// void SDL2Map::_renderObjects(
// 	TextureManager *manager, Game *game,
// 	int displayShiftX, int displayShiftY,
// 	int x, int y
// ) {
// 	E_Object *object = m_map.getObjectAt(x, y);
// 	if (object == NULL) {
// 		return;
// 	}
//
// 	S_ObjectData objectData = m_map.getObjectData(*object);
// 	S_Coordinates position = {x, y};
// 	m_graphicFactory.getGraphicObject()->render(
// 		manager,
// 		game,
// 		displayShiftX,
// 		displayShiftY,
// 		objectData,
// 		position
// 	);
// }
//
// void SDL2Map::_renderActors(int displayShiftX, int displayShiftY, int x, int y) {
// 	std::shared_ptr<Actor> actor = m_map.getActorAt(x, y);
// 	if (actor == NULL) {
// 		return;
// 	}
//
// 	actor->render(displayShiftX, displayShiftY);
// }
