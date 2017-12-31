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

class City {
	friend class CityGenerator;
	friend class Save;
	private:
	S_CityInfo m_info;
	const int width = CITY_WIDTH;
	const unsigned int size = CITY_SIZE;
	char grid[CITY_SIZE];

	public:
	City(S_CityInfo info) : m_info(info) {}
};

#endif
