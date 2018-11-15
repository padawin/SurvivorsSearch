#ifndef __SAVE__
#define __SAVE__

#include <string>
#include <memory>
#include "types.hpp"

class World;
class City;
class GameActor;

class Save {
	private:
	static void _loadPlayer(std::shared_ptr<GameActor> player, char cityInternalName[20]);
	static void _loadCity(City &city, char cityName[20]);
	static void _saveCityLine(FILE *mapFile, S_CityInfo &city);
	static bool _saveWorld(World &world);
	static bool _saveCity(City &city);
	static bool _savePlayer(std::shared_ptr<GameActor> player, City &city);

	public:
	static bool exists();
	static void clean();

	static void create(std::shared_ptr<GameActor> player, City &city);
	static void load(std::shared_ptr<GameActor> player, City &city);
};

#endif
