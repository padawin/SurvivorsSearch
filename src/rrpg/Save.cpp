#include <sys/stat.h>
#include "../game/Utils.hpp"
#include "./Save.hpp"
#include "MapManager.hpp"

const char* PLAYER_FILE = "player.dat";

Save::Save(std::shared_ptr<Actor> player, std::shared_ptr<Map> map) :
	m_player(player),
	m_map(map) {
}

bool Save::exists() {
	struct stat st;
	std::string playerPath = Utils::getDataPath() + "/" + PLAYER_FILE;
	return stat(playerPath.c_str(), &st) != -1;
}

void Save::load() {
	return;
}

void Save::create() {
	Utils::createFolder(Utils::getDataPath().c_str());
	if (_loadStartMap()) {
		// create player
		_placePlayerOnMap(std::shared_ptr<Actor> player, std::shared_ptr<Map> map);
	}
}

bool Save::_loadStartMap() {
	std::string mapFile = std::string(GAME_START_MAP) + "-0";
	S_MapSpecs specs;
	strncpy(specs.name, GAME_START_MAP, MAX_LENGTH_MAP_NAME);
	specs.level = 0;
	specs.type = CAVE;
	specs.width = 20;
	specs.height = 20;
	specs.hasEnemies = false;
	return _loadMap(mapFile, specs);
}

bool Save::_loadMapAtLevel(std::string mapName, int level) {
	std::string mapFile = m_map->getKeyName(mapName, level);
	S_MapSpecs specs;
	strncpy(specs.name, mapName.c_str(), MAX_LENGTH_MAP_NAME);
	specs.level = level;
	specs.type = CAVE;
	specs.width = 50;
	specs.height = 50;
	specs.hasEnemies = true;
	return _loadMap(mapFile, specs);
}

bool Save::_loadMap(std::string mapFile, S_MapSpecs specs) {
	MapManager manager;
	std::string prevMapKey = m_map->getKeyName();
	if (manager.mapExists(mapFile)) {
		if (!manager.loadMap(m_map, mapFile)) {
			return false;
		}
	}
	else {
		return manager.generateMap(m_map, mapFile, specs);
	}
	return true;
}

void Save::_placePlayerOnMap() {
	int x, y;
	S_Coordinates *startPoint = m_map->getMapJunction(prevMapKey);
	if (startPoint == NULL) {
		x = (int) m_map->getStartPoint().getX();
		y = (int) m_map->getStartPoint().getY();
	}
	else {
		x = startPoint->x;
		y = startPoint->y;
	}

	m_map->initEnemies(m_actorFactory);
	m_map->setTileFile(m_sTilesFile.c_str());
	m_map->setObjectsFile(m_sObjectsFile.c_str());
	m_player->setX(x);
	m_player->setY(y);
	m_map->addActor(m_player);
}
