#ifndef __MAP__
#define __MAP__

#include "MapContent.hpp"

class Map {
	protected:
	unsigned int m_iSize = 0;
	char *grid = 0;
	char *visitedGrid = 0;

	MapContent m_content = MapContent();

	int _getCoordsKey(int x, int y) const;

	public:
	virtual ~Map();
	virtual void init();
	virtual int getWidth() const { return 0; }
	virtual int getHeight() const { return 0; }
	virtual unsigned int getSize() const;
	virtual unsigned char getCell(const int x, const int y) const;
	virtual void setCell(const int x, const int y, char c);
	void addActor(std::shared_ptr<Actor> actor);
	void removeActor(int x, int y);
	std::unordered_map<int, std::shared_ptr<Actor> > getActors();
	std::shared_ptr<Actor> getActorAt(int x, int y) const;
	bool moveActor(Actor* actor, int newX, int newY);
	bool areCoordinatesValid(int x, int y) const;
	bool isCellWalkable(int x, int y) const;
	bool isCellObstructingView(int x, int y) const;
	bool isCellVisited(int x, int y) const;
	void setCellVisited(int x, int y);
};

#endif
