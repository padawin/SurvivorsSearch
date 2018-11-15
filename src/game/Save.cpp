#include "Save.hpp"
#include <fstream>
#include <string.h>
#include <sys/stat.h>
#include "../Utils.hpp"
#include "World.hpp"
#include "WorldGenerator.hpp"
#include "City.hpp"
#include "CityGenerator.hpp"
#include "ActorFactory.hpp"

#define SIZE_SCRIPT_NAME 64

const char* WORLD_FILE = "world.dat";
const char* PLAYER_FILE = "player.dat";

bool Save::exists() {
	struct stat st;
	std::string worldPath = Utils::getDataPath() + "/" + WORLD_FILE;
	return stat(worldPath.c_str(), &st) != -1;
}

void Save::clean() {
	Utils::emptyFolder(Utils::getDataPath().c_str());
}

void Save::create(std::shared_ptr<GameActor> player, City &city) {
	World world;
	Utils::createFolder(Utils::getDataPath().c_str());
	WorldGenerator worldGenerator;
	worldGenerator.generate(world);
	_saveWorld(world);

	city.init();
	city.m_info = world.m_vCities[(unsigned) rand() % world.m_vCities.size()];
	CityGenerator cityGenerator;
	int startX = 0,
		startY = 0;
	cityGenerator.generate(city, &startX, &startY);
	_saveCity(city);

	// Create player save file
	player->m_location.x = startX;
	player->m_location.y = startY;
	_savePlayer(player, city);
}

void Save::_saveCityLine(FILE *mapFile, S_CityInfo &city) {
	fprintf(
		mapFile,
		"c %s %s %d %d %d %d\n",
		city.name,
		city.internalName,
		city.location.x,
		city.location.y,
		city.visited,
		city.count_survivors
	);
}

bool Save::_saveWorld(World &world) {
	std::string worldPath = Utils::getDataPath() + "/" + WORLD_FILE;
	FILE *mapFile = fopen(worldPath.c_str(), "w");
	if (mapFile == NULL) {
		return false;
	}

	for (auto city : world.m_vCities) {
		_saveCityLine(mapFile, city);
	}

	fclose(mapFile);
	return true;
}

bool Save::_saveCity(City &city) {
	char cityFile[30];
	snprintf(cityFile, 30, "city.%s.dat", city.m_info.internalName);
	std::string cityPath = Utils::getDataPath() + "/" + cityFile;
	FILE *mapFile = fopen(cityPath.c_str(), "w");
	if (mapFile == NULL) {
		return false;
	}

	_saveCityLine(mapFile, city.m_info);
	for (auto actor : city.getActors()) {
		fprintf(
			mapFile,
			"a %d %d %d %d %s\n",
			actor.second->getRace(),
			actor.second->getType(),
			actor.second->getLocation().x,
			actor.second->getLocation().y,
			actor.second->getScript().c_str()
		);
	}
	fprintf(mapFile, "\n");
	for (unsigned int cell = 0; cell < city.m_iSize; ++cell) {
		fprintf(mapFile, "%c", city.grid[cell]);
	}

	fclose(mapFile);
	return true;
}

bool Save::_savePlayer(std::shared_ptr<GameActor> player, City &city) {
	std::string playerPath = Utils::getDataPath() + "/" + PLAYER_FILE;
	FILE *playerFile = fopen(playerPath.c_str(), "w");
	if (playerFile == NULL) {
		return false;
	}

	fprintf(playerFile, "c %s\n", city.m_info.internalName);
	fprintf(playerFile, "l %d %d\n", player->m_location.x, player->m_location.y);
	fprintf(playerFile, "h %d\n", player->m_iHealth);

	fclose(playerFile);
	return true;
}

void Save::load(std::shared_ptr<GameActor> player, City &city) {
	char cityName[20];
	_loadPlayer(player, cityName);
	_loadCity(city, cityName);
}

void Save::_loadPlayer(std::shared_ptr<GameActor> player, char cityInternalName[20]) {
	std::ifstream fin;
	std::string file = Utils::getDataPath() + "/" + PLAYER_FILE;
	fin.open(file.c_str());
	if (!fin.good()) {
		fin.close();
		return;
	}

	while (!fin.eof()) {
		char line[50];
		fin.getline(line, 50);

		char type = *line;
		if (type == 'c') {
			sscanf(line, "c %s\n", cityInternalName);
		}
		else if (type == 'l') {
			sscanf(line, "l %d %d\n", &player->m_location.x, &player->m_location.y);
		}
		else if (type == 'h') {
			sscanf(line, "h %d\n", &player->m_iHealth);
		}
	}

	fin.close();
}

void Save::_loadCity(City &city, char cityName[20]) {
	std::ifstream fin;
	char cityFile[30];
	snprintf(cityFile, 30, "city.%s.dat", cityName);
	std::string file = Utils::getDataPath() + "/" + cityFile;
	fin.open(file.c_str());
	if (!fin.good()) {
		fin.close();
		return;
	}

	char line[50];
	fin.getline(line, 50);
	int visited;
	sscanf(
		line,
		"c %s %s %d %d %d %d\n",
		city.m_info.name,
		city.m_info.internalName,
		&city.m_info.location.x,
		&city.m_info.location.y,
		&visited,
		&city.m_info.count_survivors
	);
	while (true) {
		fin.getline(line, 50);
		if (line[0] == '\0') {
			break;
		}
		int x, y, race, type;
		char script[SIZE_SCRIPT_NAME] = "";
		sscanf(line, "a %d %d %d %d %s\n", &race, &type, &x, &y, script);
		std::shared_ptr<GameActor> survivor(
			ActorFactory::createActor((E_ActorRace) race, (E_ActorType) type)
		);
		survivor->setX(x);
		survivor->setY(y);
		survivor->setScript(script);
		city.addActor(survivor);
	}
	city.m_info.visited = visited;
	fin.read(city.grid, city.m_iSize);
	fin.close();
}
