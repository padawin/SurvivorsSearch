#ifndef __SAVE__
#define __SAVE__

#include <string>
#include <memory>
#include "types.hpp"

class World;
class City;
class Actor;

class Save {
	private:
	static void _loadPlayer(std::shared_ptr<Actor> player, char cityInternalName[20]);
	static void _loadCity(City &city, char cityName[20]);
	static void _saveCity(FILE *mapFile, S_CityInfo &city);

	public:
	static void loadWorld(World& world);
	static void loadCity(std::string internalName, City& city);
	static bool exists();
	static void clean();
	static void create(std::shared_ptr<Actor> player, City &city);
	static bool saveWorld(World &world);
	static bool saveCity(City &city);
	static bool savePlayer(std::shared_ptr<Actor> player, City &city);

	static void load(std::shared_ptr<Actor> player, City &city);
};

#endif
