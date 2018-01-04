#ifndef __SAVE__
#define __SAVE__

#include <string>
#include "types.hpp"

class World;
class City;
class Actor;

class Save {
	private:
	static void _loadPlayer(Actor &player);
	static void _loadCity(City &city, char cityName[20]);
	static void _saveCity(FILE *mapFile, S_CityInfo &city);

	public:
	static void loadWorld(World& world);
	static void loadCity(std::string internalName, City& city);
	static bool exists();
	static void clean();
	static void create(Actor &player, City &city);
	static bool saveWorld(World &world);
	static bool saveCity(City &city);
	static bool savePlayer(Actor &player);

	static void load(Actor &player, City &city);
};

#endif
