#ifndef __SAVE__
#define __SAVE__

#include <string>

class World;
class City;
class Player;

class Save {
	public:
	static void loadWorld(World& world);
	static void loadCity(std::string internalName, City& city);
	static bool exists();
	static void clean();
	static void create();
	static bool saveWorld(World &world);
	static bool saveCity(City &city);
	static bool savePlayer(Player &player);
};

#endif
