#ifndef __CAVE__
#define __CAVE__

#include "../Map.hpp"
#include "../Vector2D.hpp"
// #include <memory>
// #include <stdint.h>
// #include <vector>
// #include <unordered_map>
// #include "Terrain.hpp"
// #include "types.hpp"
// #include "GUI/Factory.hpp"
// #include "ResourceManager.hpp"

class Actor;
class ActorFactory;
class MapEvent;
class Vector2D;

const int WALKABLE_CONSTRAINT_ACTOR_IS_BLOCKING = 0x1;
const int WALKABLE_CONSTRAINT_ACTOR_SPAWN_LOCATION = 0x2;

class Cave : public Map {
	private:
	static MyUnorderedMap<E_MapType, std::vector<S_EnemyProbability>> s_mEnemiesPerMapType;

	E_MapType m_type = DEFAULT;
	std::string m_sName = "";
	int m_iLevel = 0;
	Vector2D m_sStartPoint = Vector2D(0, 0);
	MyUnorderedMap<E_TerrainType, Terrain*> m_mTerrains = {};
	std::unordered_map<std::string, std::pair<S_Coordinates, S_MapChangeEventData>> m_mEvents = {};
	// map of mapnames -> coordinates, list the maps linked to the current one
	// and where in the maps the player would arrive
	std::unordered_map<std::string, S_Coordinates> m_mMapJunctions = {};
	std::unordered_map<std::string, std::pair<S_Coordinates, E_Object>> m_mObjects = {};
	std::vector<S_Coordinates> m_vEnemySpawnableCells = {};

	static void _initEnemiesPerMapType();
	static std::string _getCoordsKey(int x, int y);
	int _getSameNeighbours(int x, int y);

	protected:
	Terrain *_getTerrain(E_TerrainType type);

	public:
	~Cave();

	void clear();
	std::string getKeyName(std::string name = "", int level = -1);
	void setName(std::string name);
	void setLevel(int level);
	std::string getName();
	int getLevel();

	void initializeGrid(E_TerrainType type);
	void setType(E_MapType type);
	void setTileFile(const char *tileFilePath);
	void setObjectsFile(const char *objectsFilePath);
	void setDimensions(int x, int y);
	void setTile(int x, int y, E_TerrainType type);
	void setStartPoint(float x, float y);

	void clearDeadActors();

	bool isCellWalkable(int x, int y, unsigned int walkableConstraint = 0);
	E_MapType getType();
	Vector2D getStartPoint();
	std::vector<E_TerrainType>* getGrid();
	void setGrid(std::vector<E_TerrainType> grid);

	size_t getTileIndex(int x, int y);

	void addEnemySpawnableCell(char x, char y);
	std::vector<S_Coordinates> getEnemySpawnableCells();
	void initEnemies(ActorFactory &actorFactory);

	bool hasEvent(const int x, const int y);
	S_MapChangeEventData getEvent(const int x, const int y);
	void addEvent(int x, int y, S_MapChangeEventData event);
	std::unordered_map<std::string, std::pair<S_Coordinates, S_MapChangeEventData>> &getEvents();

	S_Coordinates *getMapJunction(std::string mapKeyName);

	void addObject(int x, int y, E_Object object);
	std::unordered_map<std::string, std::pair<S_Coordinates, E_Object>> getObjects();
	S_ObjectData getObjectData(const E_Object objectType);
	E_Object *getObjectAt(int x, int y);
};

#endif
