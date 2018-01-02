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
		m_iSize = 121900;
		m_iHeight = (signed) m_iSize / m_iWidth;
		grid = (char*) malloc(m_iSize * sizeof (char));
		visitedGrid = (char*) malloc(m_iSize * sizeof (char));
		memset(visitedGrid, 0, m_iSize);
	}
	~City() {
		free(grid);
	}
};

#endif
