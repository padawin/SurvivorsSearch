#ifndef __MAP__
#define __MAP__

#include "MapContent.hpp"

class Map {
	protected:
	int m_iWidth = 0;
	int m_iHeight = 0;
	unsigned int m_iSize = 0;
	char *grid = 0;

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
	bool moveActor(Actor* actor, int newX, int newY);
	bool areCoordinatesValid(int x, int y);
	bool isCellWalkable(int x, int y);
};

#endif
