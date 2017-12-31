#ifndef __CITY_GENERATOR__
#define __CITY_GENERATOR__

#include "City.hpp"
#include <vector>

typedef struct {
	int index = 0;
	int size = 0;
} S_Block;

class CityGenerator {
	private:
	void _generateGridCity(City& city);
	void _generateVerticalRoads(City& city);
	void _generateHorizontalRoads(City& city);
	void _divideVerticalBlock(City& city, S_Block block);
	void _divideHorizontalBlock(City& city, S_Block block);

	public:
	void generate(City& city);
};

#endif
