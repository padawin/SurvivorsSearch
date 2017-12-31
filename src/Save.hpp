#ifndef __SAVE__
#define __SAVE__

#include <string>

class World;
class City;

class Save {
	public:
	static void loadWorld(World& world);
	static void loadCity(std::string internalName, City& city);
	static bool exists();
	static void clean();
	static void create();
};

#endif
