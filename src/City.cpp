#include "City.hpp"

unsigned char City::getCell(const int x, const int y) const {
	int gridIndex = y * width + x;
	return static_cast<unsigned char>(grid[gridIndex]);
}
