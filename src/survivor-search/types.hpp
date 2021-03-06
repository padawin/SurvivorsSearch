#ifndef __TYPES__
#define __TYPES__

#include <string>
#include "../game/types.hpp"

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
enum E_Behaviours : short {BEHAVIOUR_PLAYER, BEHAVIOUR_ZOMBIE};

// int is the perthousand of chance of encounter
typedef struct {
	E_ActorRace race;
	int from;
	int to;
} S_EnemyProbability;

enum E_Event : short {
	PLAYER_ATTACK, PLAYER_ATTACKED, PLAYER_SEEN,
	SURVIVOR_SAVED,
	INTRO_DIALOGUE, TUTORIAL
};

#endif
