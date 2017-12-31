#include "WorldGenerator.hpp"
#include <set>
#include <string>
#include <sstream>
#include <string.h>

const int WORLD_WIDTH = 80;
const int WORLD_HEIGHT = 35;
const char MAX_SURVIVORS_PER_CITY = 5;

void WorldGenerator::generate(World& world) {
	_generateCities(world);
	_linkCities();
}

void WorldGenerator::_generateCities(World& world) {
	std::vector<std::pair<std::string, std::string>> cities;
	_loadCities(cities);

	unsigned long minNbCities = cities.size() - cities.size() / 3;
	unsigned long maxNbCities = cities.size();
	// generate the number of cities N
	unsigned long nbCities = minNbCities + (unsigned) rand() % (maxNbCities - minNbCities);
	// generate N coordinates
	int minCoord = 0;
	int maxCoord = WORLD_WIDTH * WORLD_HEIGHT;
	std::set<int> cityCoordinates;
	unsigned long cityIndex = 0;
	do {
		auto currCity = cities[cityIndex];
		int c = minCoord + rand() % (maxCoord - minCoord);
		int nbSurvivors = 1 + rand() % MAX_SURVIVORS_PER_CITY;
		if (cityCoordinates.find(c) != cityCoordinates.end()) {
			continue;
		}

		world.m_vCities.push_back(S_CityInfo());
		S_CityInfo &city = world.m_vCities[cityIndex];
		strncpy(city.name, currCity.first.c_str(), currCity.first.size());
		strncpy(city.internalName, currCity.second.c_str(), currCity.second.size());
		city.location.x = c % WORLD_WIDTH;
		city.location.y = c / WORLD_WIDTH;
		city.count_survivors = (char) nbSurvivors;
		cityCoordinates.insert(c);
		++cityIndex;
	} while (cityIndex < nbCities);
}

void WorldGenerator::_linkCities() {
	// @TODO Implement
}

void WorldGenerator::_loadCities(std::vector<std::pair<std::string, std::string>> &cities) {
	cities = {
		{"Penarth", "penarth"},
		{"Tremadog", "tremadog"},
		{"Trefdraeth", "trefdraeth"},
		{"Abermaw", "abermaw"},
		{"Penmaenbach", "penmaenbach"},
		{"Bardsey", "bardsey"},
		{"Llanrwst", "llanrwst"},
		{"Newtown", "newtown"},
		{"Tyddewi", "tyddewi"},
		{"Ardudwy", "ardudwy"},
		{"Nevern", "nevern"},
		{"Talybont", "talybont"},
		{"Brecon", "brecon"},
		{"Rhayader", "rhayader"},
		{"Pwllheli", "pwllheli"},
		{"Chepstow", "chepstow"},
		{"Prestatyn", "prestatyn"},
		{"Beddgelert", "beddgelert"},
		{"Barmouth", "barmouth"},
		{"Aberdovey", "aberdovey"}
	};
}
