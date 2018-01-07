#include "Save.hpp"
#include <fstream>
#include <string.h>
#include <sys/stat.h>
#include "Utils.hpp"
#include "World.hpp"
#include "WorldGenerator.hpp"
#include "City.hpp"
#include "CityGenerator.hpp"
#include "Actor.hpp"

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

void Save::create(std::shared_ptr<Actor> player, City &city) {
	World world;
	Utils::createFolder(Utils::getDataPath().c_str());
	WorldGenerator worldGenerator;
	worldGenerator.generate(world);
	saveWorld(world);

	city.init();
	city.m_info = world.m_vCities[(unsigned) rand() % world.m_vCities.size()];
	CityGenerator cityGenerator;
	int startX = 0,
		startY = 0;
	cityGenerator.generate(city, &startX, &startY);
	saveCity(city);

	// Create player save file
	player->m_location.x = startX;
	player->m_location.y = startY;
	savePlayer(player, city);
}

void Save::_saveCity(FILE *mapFile, S_CityInfo &city) {
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

bool Save::saveWorld(World &world) {
	std::string worldPath = Utils::getDataPath() + "/" + WORLD_FILE;
	FILE *mapFile = fopen(worldPath.c_str(), "w");
	if (mapFile == NULL) {
		return false;
	}

	for (auto city : world.m_vCities) {
		_saveCity(mapFile, city);
	}

	fclose(mapFile);
	return true;
}

bool Save::saveCity(City &city) {
	char cityFile[30];
	snprintf(cityFile, 30, "city.%s.dat", city.m_info.internalName);
	std::string cityPath = Utils::getDataPath() + "/" + cityFile;
	FILE *mapFile = fopen(cityPath.c_str(), "w");
	if (mapFile == NULL) {
		return false;
	}

	_saveCity(mapFile, city.m_info);
	for (auto actor : city.getActors()) {
		fprintf(
			mapFile,
			"a %d %d\n",
			actor.second->getLocation().x,
			actor.second->getLocation().y
		);
	}
	fprintf(mapFile, "\n");
	for (unsigned int cell = 0; cell < city.m_iSize; ++cell) {
		fprintf(mapFile, "%c", city.grid[cell]);
	}

	fclose(mapFile);
	return true;
}

bool Save::savePlayer(std::shared_ptr<Actor> player, City &city) {
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

void Save::load(std::shared_ptr<Actor> player, City &city) {
	char cityName[20];
	_loadPlayer(player, cityName);
	_loadCity(city, cityName);
}

void Save::_loadPlayer(std::shared_ptr<Actor> player, char cityInternalName[20]) {
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
		int x, y;
		sscanf(line, "a %d %d\n", &x, &y);
		std::shared_ptr<Actor> survivor(new Actor(HUMAN, SURVIVOR));
		survivor->setX(x);
		survivor->setY(y);
		city.addActor(survivor);
	}
	city.m_info.visited = visited;
	fin.read(city.grid, city.m_iSize);
	fin.close();
}
