#ifndef __MAP__
#define __MAP__

#include "MapContent.hpp"

class Map {
	protected:
	int width = 0;
	unsigned int size = 0;
	char *grid = 0;

	MapContent m_content = MapContent();

	int _getCoordsKey(int x, int y);

	public:
	virtual ~Map() {}
	int getWidth();
	unsigned int getSize();
	virtual unsigned char getCell(const int x, const int y) const;
	void addActor(Actor *actor);
	std::unordered_map<int, Actor*> getActors();
};

#endif
