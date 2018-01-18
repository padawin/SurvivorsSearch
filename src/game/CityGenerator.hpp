#ifndef __CITY_GENERATOR__
#define __CITY_GENERATOR__

#include "City.hpp"
#include "Actor.hpp"
#include "types.hpp"
#include <vector>
#include <map>

typedef struct {
	int index = 0;
	int size = 0;
} S_Block;

class CityGenerator {
	private:
	std::map<int, std::vector<int>> m_mTypeCells = {};

	static const S_EnemyProbability s_aEnemyProbabilities[];

	void _addCellType(int type, int index);

	void _generateGridCity(City& city);
	void _generateVerticalRoads(City& city);
	void _generateHorizontalRoads(City& city, std::vector<S_Rectangle> &blocks);
	void _divideVerticalBlock(City& city, S_Block block);
	void _divideHorizontalBlock(City& city, S_Block block, std::vector<S_Rectangle> &blocks);
	void _findCityBlocks(City& city, std::vector<S_Rectangle>& blocks, int y, int height);
	void _transformBlocks(City& city, std::vector<S_Rectangle>& blocks);
	void _buildPark(City& city, S_Rectangle& block);
	void _buildPool(City& city, S_Rectangle& block);
	void _buildInterior(City& city, S_Rectangle& block);
	bool _placeStartNPC(City &city, int *startX, int *startY);
	void _addActor(City &city, int cell, E_ActorRace race, E_ActorType type, const char *script = 0);
	void _addEnemies(City &city);

	public:
	void generate(City& city, int *startX = 0, int *startY = 0);
};

#endif
