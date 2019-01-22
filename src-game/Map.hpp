#ifndef __MAP__
#define __MAP__

#include "Terrain.hpp"
#include "MapContent.hpp"
#include "commonTypes.hpp"
#include "ResourceManager.hpp"

const int NEIGHBOUR_NORTH = 1;
const int NEIGHBOUR_WEST = 2;
const int NEIGHBOUR_EAST = 4;
const int NEIGHBOUR_SOUTH = 8;
const int CURRENT_CELL = 16;

class Map {
	protected:
	unsigned int m_iSize = 0;
	std::vector<E_TerrainType> grid;
	char *visitedGrid = 0;

	// Caching of the tiles data
	MyUnorderedMap<E_TerrainTile, S_TileData> m_mTerrainsTileData;

	MapContent m_content = MapContent();
	ResourceManager<S_TileData> m_tilesManager;

	unsigned long _getCoordsKey(int x, int y) const;
	int _getSameNeighbours(int x, int y);

	virtual Terrain *_getTerrain(E_TerrainType type) = 0;

	public:
	virtual ~Map();
	virtual void init();
	virtual int getWidth() const = 0;
	virtual int getHeight() const = 0;
	virtual unsigned int getSize() const;
	virtual E_TerrainType getCell(const int x, const int y) const;
	virtual void setCell(const int x, const int y, E_TerrainType c);
	void addActor(std::shared_ptr<Actor> actor);
	void removeActor(int x, int y);
	std::unordered_map<long unsigned, std::shared_ptr<Actor> > getActors();
	std::shared_ptr<Actor> getActorAt(int x, int y) const;
	bool moveActor(Actor* actor, int newX, int newY);
	bool areCoordinatesValid(int x, int y) const;
	bool isCellWalkable(int x, int y) const;
	bool isCellObstructingView(int x, int y) const;
	bool isCellVisited(int x, int y) const;
	void setCellVisited(int x, int y);
	S_TileData getTerrainTileData(int visibleNeighbours, int x, int y);
};

#endif
