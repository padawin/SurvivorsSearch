#include "WorldGenerator.hpp"
#include <set>
#include <string>
#include <sstream>

const int WORLD_WIDTH = 80;
const int WORLD_HEIGHT = 35;

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
		int c = minCoord + rand() % (maxCoord - minCoord);
		if (cityCoordinates.find(c) != cityCoordinates.end()) {
			continue;
		}

		world.m_vCities.push_back({
			cities[cityIndex].first,
			cities[cityIndex].second,
			{c % WORLD_WIDTH, c / WORLD_WIDTH},
			false
		});
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
