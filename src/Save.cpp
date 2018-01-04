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

void Save::create(Actor &player, City &city) {
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
	strncpy(player.m_sCity, city.m_info.internalName, 20);
	player.m_location.x = startX;
	player.m_location.y = startY;
	savePlayer(player);
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
	for (auto survivor : city.m_mSurvivors) {
		fprintf(mapFile, "s %d %d\n", survivor.first, survivor.second);
	}
	for (unsigned int cell = 0; cell < city.m_iSize; ++cell) {
		fprintf(mapFile, "%c", city.grid[cell]);
	}

	fclose(mapFile);
	return true;
}

bool Save::savePlayer(Actor &player) {
	std::string playerPath = Utils::getDataPath() + "/" + PLAYER_FILE;
	FILE *playerFile = fopen(playerPath.c_str(), "w");
	if (playerFile == NULL) {
		return false;
	}

	fprintf(playerFile, "c %s\n", player.m_sCity);
	fprintf(playerFile, "l %d %d\n", player.m_location.x, player.m_location.y);
	fprintf(playerFile, "h %d\n", player.m_iHealth);

	fclose(playerFile);
	return true;
}

void Save::load(Actor &player, City &city) {
	_loadPlayer(player);
	_loadCity(city, player.m_sCity);
}

void Save::_loadPlayer(Actor &player) {
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
			sscanf(line, "c %s\n", player.m_sCity);
		}
		else if (type == 'l') {
			sscanf(line, "l %d %d\n", &player.m_location.x, &player.m_location.y);
		}
		else if (type == 'h') {
			sscanf(line, "h %d\n", &player.m_iHealth);
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
	for (int s = 0; s < city.m_info.count_survivors; ++s) {
		char survivor[50];
		fin.getline(survivor, 50);
		// std::getline(read, x);
		int cellIndex, saved;
		sscanf(survivor, "s %d %d\n", &cellIndex, &saved);
		city.addSurvivor(cellIndex, (bool) saved);
	}
	city.m_info.visited = visited;
	fin.read(city.grid, city.m_iSize);
	fin.close();
}
