#ifndef __CITY__
#define __CITY__

#include "types.hpp"
#include "Map.hpp"
#include <string.h>

class City : public Map {
	friend class CityGenerator;
	friend class Save;
	private:
	S_CityInfo m_info = S_CityInfo();

	public:
	City() {
		m_iWidth = 530;
		m_iHeight = 230;
		m_iSize = (unsigned) (m_iWidth * m_iHeight);
		grid = (char*) malloc(m_iSize * sizeof (char));
		visitedGrid = (char*) malloc(m_iSize * sizeof (char));
		memset(visitedGrid, 0, m_iSize);
	}
	~City() {
		free(grid);
	}
};

#endif
