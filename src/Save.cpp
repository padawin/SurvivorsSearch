#include "Save.hpp"
#include <sys/stat.h>
#include "Utils.hpp"
#include "World.hpp"
#include "WorldGenerator.hpp"

const std::string WORLD_FILE = "world.dat";
const std::string CITY_FILE = "city.%s.dat";
const std::string PLAYER_FILE = "player.dat";

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
			"c %s %s %d %d %d\n",
			city.name,
			city.internalName,
			city.location.x,
			city.location.y,
			city.visited
		);
	}

	fclose(mapFile);
	return true;
}
