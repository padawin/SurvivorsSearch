#include "CityGenerator.hpp"
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

void CityGenerator::generate(City& city) {
	_generateGridCity(city);
}

void CityGenerator::_generateGridCity(City& city) {
	memset(city.grid, WALL_TILE, CITY_SIZE);
	// make vertical roads
	_generateVerticalRoads(city);
	// make horizontal roads
	_generateHorizontalRoads(city, blocks);
}

void CityGenerator::_generateVerticalRoads(City& city) {
	S_Block b;
	b.index = 0;
	b.size = city.width;
	_divideVerticalBlock(city, b);
}

void CityGenerator::_generateHorizontalRoads(City& city) {
	S_Block b;
	b.index = 0;
	b.size = CITY_SIZE / CITY_WIDTH;
	_divideHorizontalBlock(city, b);
}

void CityGenerator::_divideVerticalBlock(City& city, S_Block block) {
	if (block.size < MIN_DIVIDABLE_WIDTH) {
		return;
	}

	int widthRoad = MIN_WIDTH_ROAD + rand() % (MAX_WIDTH_ROAD - MIN_WIDTH_ROAD + 1);
	int divideIndex = block.index + MIN_WIDTH_BLOCK + rand() % (block.size - 2 * MIN_WIDTH_BLOCK);
	for (int j = divideIndex; j < CITY_SIZE; j += CITY_WIDTH) {
		city.grid[j] = PAVEMENT_TILE;
		for (int r = 1; r <= widthRoad; ++r) {
			city.grid[j + r] = ROAD_TILE;
		}
		city.grid[j + widthRoad + 1] = PAVEMENT_TILE;
	}

	S_Block bLeft = block;
	bLeft.size = divideIndex - bLeft.index;
	S_Block bRight = block;
	bRight.index = divideIndex + 2 + widthRoad;
	bRight.size = block.index + block.size - divideIndex - 2 - widthRoad;
	_divideVerticalBlock(city, bLeft);
	_divideVerticalBlock(city, bRight);
}

void CityGenerator::_divideHorizontalBlock(City& city, S_Block block) {
	if (block.size < MIN_DIVIDABLE_HEIGHT) {
		return;
	}

	int widthRoad = MIN_WIDTH_ROAD + rand() % (MAX_WIDTH_ROAD - MIN_WIDTH_ROAD + 1);
	int divideIndex = block.index + MIN_HEIGHT_BLOCK + rand() % (block.size - 2 * MIN_HEIGHT_BLOCK);
	for (int i = divideIndex * CITY_WIDTH; i < (1 + divideIndex) * CITY_WIDTH; ++i) {
		city.grid[i] = PAVEMENT_TILE;
		for (int r = 1; r <= widthRoad; ++r) {
			city.grid[i + r * CITY_WIDTH] = ROAD_TILE;
		}
		city.grid[i + (widthRoad + 1) * CITY_WIDTH] = PAVEMENT_TILE;
	}

	S_Block bUp = block;
	bUp.size = divideIndex - bUp.index;
	S_Block bBottom = block;
	bBottom.index = divideIndex + 2 + widthRoad;
	bBottom.size = block.index + block.size - divideIndex - 2 - widthRoad;
	_divideHorizontalBlock(city, bUp);
	_divideHorizontalBlock(city, bBottom);
}
