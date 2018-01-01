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

void Save::create() {
	World world;
	Utils::createFolder(Utils::getDataPath().c_str());
	WorldGenerator worldGenerator;
	worldGenerator.generate(world);
	saveWorld(world);

	City city;
	city.m_info = world.m_vCities[(unsigned) rand() % world.m_vCities.size()];
	CityGenerator cityGenerator;
	int startX = 0,
		startY = 0;
	cityGenerator.generate(city, &startX, &startY);
	saveCity(city);

	// Create player save file
	Actor p;
	strncpy(p.m_sCity, city.m_info.internalName, 20);
	p.m_location.x = startX;
	p.m_location.y = startY;
	savePlayer(p);
}

bool Save::saveWorld(World &world) {
	std::string worldPath = Utils::getDataPath() + "/" + WORLD_FILE;
	FILE *mapFile = fopen(worldPath.c_str(), "w");
	if (mapFile == NULL) {
		return false;
	}

	for (auto city : world.m_vCities) {
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

	fprintf(mapFile, "n %s\n", city.m_info.name);
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
	sscanf(line, "n %s\n", city.m_info.name);
	fin.read(city.grid, city.m_iSize);
	fin.close();
}
