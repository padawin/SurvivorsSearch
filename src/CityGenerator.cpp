#include "CityGenerator.hpp"
#include "Actor.hpp"
#include <string.h>

const int MIN_WIDTH_BLOCK = 40;
const int MIN_DIVIDABLE_WIDTH = 83;
const int MIN_HEIGHT_BLOCK = 15;
const int MIN_DIVIDABLE_HEIGHT = 33;

const int MIN_WIDTH_ROAD = 1;
const int MAX_WIDTH_ROAD = 3;

const int BLOCK_BUILDING = 0;
const int BLOCK_INTERIOR = 1;
const int BLOCK_POOL = 2;
const int BLOCK_PARK = 3;

const int MIN_PROBA_PARK = 0;
const int MAX_PROBA_PARK = 4;
const int MIN_PROBA_WATER = 5;
const int MAX_PROBA_WATER = 7;
const int MIN_PROBA_INTERIOR = 8;
const int MAX_PROBA_INTERIOR = 23;

const int CAN_HAVE_FOE = 0;
const int CAN_HAVE_SURVIVOR = 1;
const int CAN_BE_START = 2;

void CityGenerator::_addCellType(int type, int index) {
	if (m_mTypeCells.find(type) == m_mTypeCells.end()) {
		m_mTypeCells[type] = {};
	}

	m_mTypeCells[type].push_back(index);
}

void CityGenerator::generate(City& city, int *startX, int *startY) {
	m_mTypeCells.empty();
	_generateGridCity(city);
	if (startX != 0 && startY != 0) {
		int startCell = m_mTypeCells[CAN_BE_START][(unsigned) rand() % m_mTypeCells[CAN_BE_START].size()];
		*startX = startCell % city.getWidth();
		*startY = startCell / city.getWidth();
	}

	// add survivors
	std::vector<int> survivorsPossibleLocations = m_mTypeCells[CAN_HAVE_SURVIVOR];
	for (unsigned long i = 0, nbSurvivors = (unsigned long) city.m_info.count_survivors; i < nbSurvivors; ++i) {
		unsigned long cellIndex = i + (unsigned long) rand() % (survivorsPossibleLocations.size() - i);
		int x = survivorsPossibleLocations[cellIndex] % city.getWidth();
		int y = survivorsPossibleLocations[cellIndex] / city.getWidth();
		std::shared_ptr<Actor> survivor(new Actor(HUMAN, SURVIVOR));
		survivor->setX(x);
		survivor->setY(y);
		city.addActor(survivor);
		std::swap(survivorsPossibleLocations[i], survivorsPossibleLocations[cellIndex]);
	}
}

void CityGenerator::_generateGridCity(City& city) {
	memset(city.grid, WALL_TILE, city.m_iSize);
	// make vertical roads
	_generateVerticalRoads(city);
	// initialise blocks
	std::vector<S_Rectangle> blocks;
	// make horizontal roads
	_generateHorizontalRoads(city, blocks);
	// transform blocks into interiors, parcs or pools
	_transformBlocks(city, blocks);
}

void CityGenerator::_generateVerticalRoads(City& city) {
	S_Block b;
	b.index = 0;
	b.size = city.getWidth();
	_divideVerticalBlock(city, b);
}

void CityGenerator::_generateHorizontalRoads(City& city, std::vector<S_Rectangle> &blocks) {
	S_Block b;
	b.index = 0;
	b.size = city.getHeight();
	_divideHorizontalBlock(city, b, blocks);
}

void CityGenerator::_divideVerticalBlock(City& city, S_Block block) {
	if (block.size < MIN_DIVIDABLE_WIDTH) {
		return;
	}

	int widthRoad = MIN_WIDTH_ROAD + rand() % (MAX_WIDTH_ROAD - MIN_WIDTH_ROAD + 1);
	int divideIndex = block.index + MIN_WIDTH_BLOCK + rand() % (block.size - 2 * MIN_WIDTH_BLOCK);
	int size = (int) city.m_iSize;
	for (int j = divideIndex; j < size; j += city.getWidth()) {
		city.grid[j] = PAVEMENT_TILE;
		_addCellType(CAN_HAVE_FOE, j);
		for (int r = 1; r <= widthRoad; ++r) {
			city.grid[j + r] = ROAD_TILE;
			_addCellType(CAN_HAVE_FOE, j + r);
		}
		city.grid[j + widthRoad + 1] = PAVEMENT_TILE;
		_addCellType(CAN_HAVE_FOE, j + widthRoad + 1);
	}

	S_Block bLeft = block;
	bLeft.size = divideIndex - bLeft.index;
	S_Block bRight = block;
	bRight.index = divideIndex + 2 + widthRoad;
	bRight.size = block.index + block.size - divideIndex - 2 - widthRoad;
	_divideVerticalBlock(city, bLeft);
	_divideVerticalBlock(city, bRight);
}

void CityGenerator::_divideHorizontalBlock(City& city, S_Block block, std::vector<S_Rectangle>& blocks) {
	if (block.size < MIN_DIVIDABLE_HEIGHT) {
		// for each block of the line, create a city block and add it to blocks
		_findCityBlocks(city, blocks, block.index, block.size);
		return;
	}

	int widthRoad = MIN_WIDTH_ROAD + rand() % (MAX_WIDTH_ROAD - MIN_WIDTH_ROAD + 1);
	int divideIndex = block.index + MIN_HEIGHT_BLOCK + rand() % (block.size - 2 * MIN_HEIGHT_BLOCK);
	for (int i = divideIndex * city.getWidth(); i < (1 + divideIndex) * city.getWidth(); ++i) {
		if (city.grid[i] == WALL_TILE) {
			city.grid[i] = PAVEMENT_TILE;
			_addCellType(CAN_HAVE_FOE, i);
		}
		int currIndex;
		for (int r = 1; r <= widthRoad; ++r) {
			currIndex = i + r * city.getWidth();
			if (city.grid[currIndex] == WALL_TILE) {
				_addCellType(CAN_HAVE_FOE, currIndex);
			}
			city.grid[currIndex] = ROAD_TILE;
		}
		currIndex = i + (widthRoad + 1) * city.getWidth();
		if (city.grid[currIndex] == WALL_TILE) {
			city.grid[currIndex] = PAVEMENT_TILE;
			_addCellType(CAN_HAVE_FOE, currIndex);
		}
	}

	S_Block bUp = block;
	bUp.size = divideIndex - bUp.index;
	S_Block bBottom = block;
	bBottom.index = divideIndex + 2 + widthRoad;
	bBottom.size = block.index + block.size - divideIndex - 2 - widthRoad;
	_divideHorizontalBlock(city, bUp, blocks);
	_divideHorizontalBlock(city, bBottom, blocks);
}

void CityGenerator::_findCityBlocks(City& city, std::vector<S_Rectangle>& blocks, int y, int height) {
	unsigned long nbBlocks = blocks.size();
	const int STATE_WALL = 0;
	const int STATE_PAVEMENT_LEFT = 1;
	const int STATE_ROAD = 2;
	const int STATE_PAVEMENT_RIGHT = 3;
	int state = STATE_PAVEMENT_RIGHT;
	for (int x = 0; x < city.getWidth(); ++x) {
		if (city.grid[x] == WALL_TILE && state == STATE_PAVEMENT_RIGHT) {
			state = STATE_WALL;
			blocks.push_back(S_Rectangle());
			blocks[nbBlocks].x = x;
			blocks[nbBlocks].y = y;
			blocks[nbBlocks].height = height;
		}
		else if (city.grid[x] == PAVEMENT_TILE && state == STATE_WALL) {
			state = STATE_PAVEMENT_LEFT;
			blocks[nbBlocks].width = x - blocks[nbBlocks].x;
			++nbBlocks;
		}
		else if (city.grid[x] == ROAD_TILE && state == STATE_PAVEMENT_LEFT) {
			state = STATE_ROAD;
		}
		else if (city.grid[x] == PAVEMENT_TILE && state == STATE_ROAD) {
			state = STATE_PAVEMENT_RIGHT;
		}
	}
}

void CityGenerator::_transformBlocks(City& city, std::vector<S_Rectangle>& blocks) {
	int nbInteriors = 0;
	for (auto block : blocks) {
		int proba = rand() % 100;
		if (MIN_PROBA_PARK <= proba && proba < MAX_PROBA_PARK) {
			_buildPark(city, block);
		}
		else if (MIN_PROBA_WATER <= proba && proba < MAX_PROBA_WATER) {
			_buildPool(city, block);
		}
		else if (
			MIN_PROBA_INTERIOR <= proba && proba < MAX_PROBA_INTERIOR
			&& block.width >= 3 && block.height >= 3
		) {
			++nbInteriors;
			_buildInterior(city, block);
		}
	}

	unsigned long indexBlock = (unsigned) rand() % blocks.size();
	while (nbInteriors < 2) {
		if (blocks[indexBlock].type == BLOCK_BUILDING) {
			_buildInterior(city, blocks[indexBlock]);
		}
		indexBlock = (indexBlock + 1) % blocks.size();
		++nbInteriors;
	}
}

void CityGenerator::_buildPark(City& city, S_Rectangle& block) {
	block.type = BLOCK_PARK;
	for (int y = block.y; y < block.y + block.height; ++y) {
		for (int x = block.x; x < block.x + block.width; ++x) {
			city.setCell(x, y, (rand() % 100) > 10 ? GRASS_TILE : TREE_TILE);
			_addCellType(CAN_HAVE_FOE, y * city.getWidth() + x);
		}
	}
}

void CityGenerator::_buildPool(City& city, S_Rectangle& block) {
	block.type = BLOCK_POOL;
	for (int y = block.y; y < block.y + block.height; ++y) {
		for (int x = block.x; x < block.x + block.width; ++x) {
			city.setCell(x, y, WATER_TILE);
		}
	}
}

void CityGenerator::_buildInterior(City& city, S_Rectangle& block) {
	block.type = BLOCK_INTERIOR;
	// add floor
	for (int y = block.y + 1; y < block.y + block.height - 1; ++y) {
		for (int x = block.x + 1; x < block.x + block.width - 1; ++x) {
			city.setCell(x, y, INTERIOR_TILE);
			_addCellType(CAN_BE_START, y * city.getWidth() + x);
			_addCellType(CAN_HAVE_SURVIVOR, y * city.getWidth() + x);
		}
	}

	// add door
	int side = rand() % 4;
	char tile;
	int x, y;
	if (side <= 1) {
		x = block.x + 1 + rand() % (block.width - 2);
		// 0 is up, 1 is down
		// set the door on the upper side if side is 0 and if the block is not
		// at the top of the map, or the room will be unreachable
		// or set it at the top if the room *is* at the bottom of the map
		if ((side == 0 && block.y > 0)
			|| (
				side == 1 &&
				(block.y + block.height) * city.getWidth() >= (signed) city.m_iSize
		   )
		) {
			y = block.y;
		}
		else {
			y = block.y + block.height - 1;
		}
		tile = HORIZ_DOOR_TILE;
	}
	else {
		y = block.y + 1 + rand() % (block.height - 2);
		// 2 is left, 3 is right
		// set the door on the upper side if side is 0 and if the block is not
		// at the top of the map, or the room will be unreachable
		// or set it at the top if the room *is* at the bottom of the map
		if ((side == 2 && block.x > 0)
			|| (
				side == 3 &&
				block.x + block.width > city.getWidth()
		   )
		) {
			x = block.x;
		}
		else {
			x = block.x + block.width - 1;
		}
		tile = VERTIC_DOOR_TILE;
	}
	city.setCell(x, y, tile);
}
