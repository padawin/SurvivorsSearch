#include "Save.hpp"
#include <sys/stat.h>
#include "Utils.hpp"
#include "World.hpp"

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
	Utils::createFolder(Utils::getDataPath().c_str());
}
