#ifndef __MAP__
#define __MAP__

#include "MapContent.hpp"

const char WALL_TILE = 0;
const char ROAD_TILE = 1;
const char PAVEMENT_TILE = 2;
const char GRASS_TILE = 3;
const char TREE_TILE = 4;
const char WATER_TILE = 5;
const char INTERIOR_TILE = 6;
const char HORIZ_DOOR_TILE = 7;
const char VERTIC_DOOR_TILE = 8;

class Map {
	protected:
	int m_iWidth = 0;
	int m_iHeight = 0;
	unsigned int m_iSize = 0;
	char *grid = 0;
	char *visitedGrid = 0;

	MapContent m_content = MapContent();

	int _getCoordsKey(int x, int y) const;

	public:
	virtual ~Map() {}
	int getWidth();
	unsigned int getSize();
	virtual unsigned char getCell(const int x, const int y) const;
	virtual void setCell(const int x, const int y, char c);
	void addActor(Actor *actor);
	std::unordered_map<int, Actor*> getActors();
	Actor* getActorAt(int x, int y) const;
	bool moveActor(Actor* actor, int newX, int newY);
	bool areCoordinatesValid(int x, int y);
	bool isCellWalkable(int x, int y);
	bool isCellObstructingView(int x, int y);
	void setCellVisited(int x, int y);
};

#endif
