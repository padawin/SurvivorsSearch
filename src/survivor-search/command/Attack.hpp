#ifndef __ATTACK_COMMAND__
#define __ATTACK_COMMAND__

#include "../game/Command.hpp"

class Actor;
class Map;

class AttackCommand : public Command {
	public:
	bool execute(Map &map, int xDest, int yDest, Actor *actor=0);
};

#endif
