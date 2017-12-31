#ifndef __TYPES__
#define __TYPES__

#include <string>

typedef struct {
	int x = -1;
	int y = -1;
} S_Coordinates;

typedef struct {
	char name[20];
	char internalName[20];
	S_Coordinates location = S_Coordinates();
	bool visited = false;
} S_CityInfo;

typedef struct {
	int city1Index;
	int city2Index;
	bool visited;
} S_CityConnection;

#endif
