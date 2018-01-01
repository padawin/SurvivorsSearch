#ifndef __CITY__
#define __CITY__

#include "types.hpp"

const int CITY_WIDTH = 530;
const int CITY_SIZE = 121900;

const char WALL_TILE = 0;
const char ROAD_TILE = 1;
const char PAVEMENT_TILE = 2;
const char GRASS_TILE = 3;
const char TREE_TILE = 4;
const char WATER_TILE = 5;
const char INTERIOR_TILE = 6;
const char HORIZ_DOOR_TILE = 7;
const char VERTIC_DOOR_TILE = 8;

class City {
	friend class CityGenerator;
	friend class Save;
	private:
	S_CityInfo m_info = S_CityInfo();
	const int width = CITY_WIDTH;
	const unsigned int size = CITY_SIZE;
	char grid[CITY_SIZE];

	public:
	unsigned char getCell(const int x, const int y) const;
};

#endif
