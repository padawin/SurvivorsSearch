#ifndef __TYPES__
#define __TYPES__

#include <string>

typedef struct {
	int x;
	int y;
} S_Coordinates;

typedef struct {
	std::string name;
	std::string internalName;
	S_Coordinates location;
	bool visited;
} S_CityInfo;

typedef struct {
	int city1Index;
	int city2Index;
	bool visited;
} S_CityConnection;

#endif
