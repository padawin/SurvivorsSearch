#ifndef __WORLD_GENERATOR__
#define __WORLD_GENERATOR__

#include "World.hpp"

class WorldGenerator {
	private:
	void _generateCities(World& world);
	void _loadCities(std::vector<std::pair<std::string, std::string>> &cities);

	public:
	void generate(World& world);
};

#endif
