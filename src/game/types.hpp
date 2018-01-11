#ifndef __TYPES__
#define __TYPES__

#include <string>
#include "../types.hpp"

typedef struct {
	char name[20];
	char internalName[20];
	S_Coordinates location = S_Coordinates();
	bool visited = false;
	int count_survivors = 0;
} S_CityInfo;

typedef struct {
	int city1Index;
	int city2Index;
	bool visited;
} S_CityConnection;

enum E_ActorType : short {PLAYER, SURVIVOR, FOE, FRIEND};
enum E_ActorRace : short {HUMAN, ZOMBIE, LARGE_ZOMBIE};

// int is the perthousand of chance of encounter
typedef struct {
	E_ActorRace race;
	int from;
	int to;
} S_EnemyProbability;

#endif
