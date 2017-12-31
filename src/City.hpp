#ifndef __CITY__
#define __CITY__

#include "types.hpp"

const int CITY_WIDTH = 530;
const int CITY_SIZE = 121900;

const char WALL_TILE = '#';
const char ROAD_TILE = '.';
const char PAVEMENT_TILE = ',';

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
