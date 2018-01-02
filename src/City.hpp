#ifndef __CITY__
#define __CITY__

#include "types.hpp"
#include "Map.hpp"
#include <string.h>

const int CITY_WIDTH = 530;
const int CITY_SIZE = 121900;

class City : public Map {
	friend class CityGenerator;
	friend class Save;
	private:
	S_CityInfo m_info = S_CityInfo();

	public:
	City() {
		m_iWidth = CITY_WIDTH;
		m_iSize = CITY_SIZE;
		m_iHeight = (signed) m_iSize / m_iWidth;
		grid = (char*) malloc(CITY_SIZE * sizeof (char));
		visitedGrid = (char*) malloc(CITY_SIZE * sizeof (char));
		memset(visitedGrid, 0, CITY_SIZE);
	}
	~City() {
		free(grid);
	}
};

#endif
