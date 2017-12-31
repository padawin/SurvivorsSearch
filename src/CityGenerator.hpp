#ifndef __CITY_GENERATOR__
#define __CITY_GENERATOR__

#include "City.hpp"
#include <vector>
#include <map>

typedef struct {
	int index = 0;
	int size = 0;
} S_Block;

typedef struct {
	int x = 0;
	int y = 0;
	int width = 0;
	int height = 0;
	int type = 0;
} S_CityBlock;

class CityGenerator {
	private:
	std::map<int, std::vector<int>> m_mTypeCells = {};

	void addCellType(int type, int index);

	void _generateGridCity(City& city);
	void _generateVerticalRoads(City& city);
	void _generateHorizontalRoads(City& city, std::vector<S_CityBlock> &blocks);
	void _divideVerticalBlock(City& city, S_Block block);
	void _divideHorizontalBlock(City& city, S_Block block, std::vector<S_CityBlock> &blocks);
	void _findCityBlocks(City& city, std::vector<S_CityBlock>& blocks, int y, int height);
	void _transformBlocks(City& city, std::vector<S_CityBlock>& blocks);
	void _buildPark(City& city, S_CityBlock& block);
	void _buildPool(City& city, S_CityBlock& block);
	void _buildInterior(City& city, S_CityBlock& block);

	public:
	void generate(City& city);
};

#endif
