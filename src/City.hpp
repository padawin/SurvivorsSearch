#ifndef __CITY__
#define __CITY__

#include "types.hpp"
#include "Map.hpp"

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

class City : public Map {
	friend class CityGenerator;
	friend class Save;
	private:
	S_CityInfo m_info = S_CityInfo();

	public:
	City() {
		width = CITY_WIDTH;
		size = CITY_SIZE;
		grid = (char*) malloc(CITY_SIZE * sizeof (char));
	}
	~City() {
		free(grid);
	}
};

#endif
