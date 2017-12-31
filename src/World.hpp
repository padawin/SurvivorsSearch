#ifndef __WORLD__
#define __WORLD__

#include "types.hpp"
#include <vector>

class World {
	friend class WorldGenerator;
	private:
	std::vector<S_CityInfo> m_vCities = {};
	std::vector<S_CityConnection> m_vCityLinks = {};
};

#endif
