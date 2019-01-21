#include "Map.hpp"

SDL2Map::SDL2Map() :
	m_camera() {
}

void SDL2Map::render(Map *map __attribute__((unused)), FieldOfView &fov __attribute__((unused)), int shiftX __attribute__((unused)), int shiftY __attribute__((unused))) {

}

void SDL2Map::setCamera(S_Rectangle camera) {
	m_camera = camera;
}
