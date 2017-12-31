#include "Save.hpp"
#include <sys/stat.h>
#include "Utils.hpp"
#include "World.hpp"
#include "WorldGenerator.hpp"
#include "City.hpp"
#include "CityGenerator.hpp"

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

	City city(world.m_vCities[(unsigned) rand() % world.m_vCities.size()]);
	CityGenerator cityGenerator;
	cityGenerator.generate(city);
	saveCity(city);
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

	fprintf(mapFile, "name %s\n", city.m_info.name);
	fprintf(mapFile, "width %d\n", city.width);
	fprintf(mapFile, "size %d\n", city.size);
	for (unsigned int cell = 0; cell < city.size; ++cell) {
		fprintf(mapFile, "%c", city.grid[cell]);
	}

	fclose(mapFile);
	return true;
}
